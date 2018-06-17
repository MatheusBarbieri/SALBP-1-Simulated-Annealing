import subprocess
import datetime
import time
import os

exe = 10
instances = {
        'MERTENS.IN2': [6, 15, 18],
        'MITCHELL.IN2': [14, 35, 26],
        'WEE-MAG.IN2': [56, 28, 36, 54]
    }
iterations = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
restarts = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
use_csv = True
verbose = False

message_template = "Running {} ({} execution) with c={}, i={}, r={}."

csv = 'instance; execution; seed; number_of_tasks; cycle_time; iterations; restarts; solution; duration;\n'

for exe in range(exe):
    exe = exe + 1
    for instance, cycle_times in instances.items():
        instance_name = instance[0:-4]

        if not use_csv:
            dir = 'salbp1-sa-outputs/{}_{}'.format(instance_name, exe)
            os.system('mkdir ' + dir)

        for c in cycle_times:
            for i in iterations:
                for r in restarts:

                    with open('instances/' + instance) as ifile:
                        execution = ["./salbp1-sa", '-c', str(c), '-i', str(i), '-r', str(r)]
                        if use_csv:
                            execution.append('-p')
                        elif verbose:
                            execution.append('-v')

                        message = message_template.format(instance_name, exe, c, i, r)
                        print(message)

                        process = subprocess.Popen(execution, stdin=ifile, stdout=subprocess.PIPE)
                        output = process.communicate()[0].decode('utf-8')

                        if use_csv:
                            csv = csv + '{}; {}; {}\n'.format(
                                instance_name,
                                str(exe),
                                output,
                            )

                        if not use_csv:
                            newfile = '{}/c{}_i{}_r{}.txt'.format(dir, c, i, r)
                            with open(newfile, 'wb') as ofile:
                                ofile.write(output)
if use_csv:
    now = datetime.datetime.now()
    with open('csv_salbp1_executions_' + now.strftime("%Y-%m-%d %H:%M"), 'wb') as ofile:
        ofile.write(csv.encode('utf-8'))
