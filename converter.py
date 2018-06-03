import sys

def new_file_name(file_name, c):
    name =file_name.split('/')[-1]
    return '{}_c_{}.mod'.format(name[0:-4], c)

if len(sys.argv) > 2:
    file_name = sys.argv[1]
    c = sys.argv[2]
else:
    print('You fool!!!\nCorrect usage:\n\tpython converter.py <filename> <cycle_time>')
    exit(0)

with open(file_name) as file:
    number_of_tasks = int(file.readline())
    task_times = []
    for i in range(number_of_tasks):
        task_times.append(int(file.readline()))
    precedence = map(lambda x: map(lambda y: int(y), x.split(',')), file.readlines())
    del precedence[-1]

    precedence_matrix = [[0]*number_of_tasks for _ in range(number_of_tasks)]

    for pred in precedence:
        precedence_matrix[pred[1]-1][pred[0]-1] = 1

    with open(new_file_name(file_name, c), 'w') as amlp:
        amlp.write('data;\n\n')
        amlp.write('param N := {};\n'.format(number_of_tasks))
        amlp.write('param S := {}; /* upper_bound */\n'.format(number_of_tasks))
        amlp.write('param c := {};\n'.format(c))
        amlp.write('param t :=\n')
        for i in range(number_of_tasks-1):
            amlp.write('\t {}\t{}\n'.format(i+1, task_times[i]))
        amlp.write('\t {}\t{};\n\nparam p :  '.format(number_of_tasks, task_times[number_of_tasks-1]))
        for i in range(number_of_tasks):
            amlp.write('{}  '.format(i+1))
        amlp.write(':=\n')
        for i in range(number_of_tasks-1):
            amlp.write('\t\t{}  {}\n'.format(i+1, '  '.join(map(lambda x: str(x), precedence_matrix[i]))))
        amlp.write('\t\t{}  {};'.format(number_of_tasks, '  '.join(map(lambda x: str(x), precedence_matrix[number_of_tasks-1]))))
