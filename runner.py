import subprocess
import time
import os

# exe = 10
# instances = {
#         'MERTENS.IN2': [6, 15, 18],
#         'MITCHELL.IN2': [14, 35, 26],
#         'WEE-MAG.IN2': [56, 28, 36, 54]
#     }
# iterations = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
# restarts = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
# verbose = True

exe = 3
instances = {
        'MERTENS.IN2': [6, 15, 18],
        'MITCHELL.IN2': [14, 35, 26],
    }
iterations = [100, 200]
restarts = [1, 2]
verbose = False

for exe in range(exe):
    for instance, cycle_times in instances.items():

        dir = 'salbp1-sa-outputs/{}_{}'.format(instance[0:-4], exe+1)
        os.system('mkdir ' + dir)

        for c in cycle_times:
            for i in iterations:
                for r in restarts:

                    with open('instances/' + instance) as ifile:
                        execution = ["./salbp1-sa", '-c', str(c), '-i', str(i), '-r', str(r)]
                        if verbose:
                            execution.append('-v')

                        process = subprocess.Popen(execution, stdin=ifile, stdout=subprocess.PIPE)
                        output = process.communicate()[0]

                        newfile = '{}/c{}_i{}_r{}.txt'.format(dir, c, i, r)
                        with open(newfile, 'wb') as ofile:
                            ofile.write(output)
