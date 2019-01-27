WIDTH = 50
HEIGHT = 50


def init_n():
    return [0] * WIDTH * HEIGHT


def write_point(n, x, y, f):
    pos = y * WIDTH + x
    n[pos] = (n[pos] + 1) % 3
    f.write(str(round(x)) + " " + str(round(y)) + " " + str(n[pos]) + '\n')


def rule_1():
    n = init_n()

    f = open("rule1.txt", "w")
    f.write('0.0 0.0 1.0\n')

    write_point(n, round(WIDTH / 2 + 2), round(HEIGHT / 2 + 2), f)
    write_point(n, round(WIDTH / 2 - 3), round(HEIGHT / 2 - 3), f)

    f.close()


def rule_2():
    n = init_n()

    f = open("rule2.txt", "w")
    f.write('0.0 0.0 1.0\n')

    for x in range(int(WIDTH / 2 - 1), int(WIDTH / 2 + 2)):
        for y in range(int(HEIGHT / 2 - 2), int(HEIGHT / 2 + 2)):
            write_point(n, round(x), round(y), f)

    for y in range(int(HEIGHT / 2 - 1), int(HEIGHT / 2 + 2)):
        write_point(n, round(WIDTH / 2) + 1, round(y), f)

    write_point(n, round(WIDTH / 2 + 0.5), round(HEIGHT / 2 + 6), f)
    write_point(n, round(WIDTH / 2 + 0.5), round(HEIGHT / 2 + 6), f)

    f.close()


def blob():
    n = init_n()

    f = open("blob.txt", "w")
    f.write('0.0 0.0 1.0\n')

    for x in range(int(WIDTH / 2 - 1), int(WIDTH / 2 + 2)):
        for y in range(int(HEIGHT / 2 - 2), int(HEIGHT / 2 + 2)):
            write_point(n, round(x), round(y), f)

    for y in range(int(HEIGHT / 2 - 1), int(HEIGHT / 2 + 2)):
        write_point(n, round(WIDTH / 2) + 1, round(y), f)

    f.close()


def chase():
    n = init_n()

    f = open("chase.txt", "w")
    f.write('0.0 0.0 1.0\n')

    for x in range(int(WIDTH / 2 - 2), int(WIDTH / 2 + 2)):
        for y in range(int(HEIGHT / 2 - 2), int(HEIGHT / 2 + 2)):
            write_point(n, round(x), round(y), f)
            if x > y:
                write_point(n, round(x), round(y), f)

    f.close()


def wave():
    n = init_n()

    f = open("wave.txt", "w")
    f.write('0.2 0.1 0.8\n')

    for x in range(round(WIDTH / 2) - 1, round(WIDTH / 2) + 2):
        for y in range(0, HEIGHT):
            write_point(n, round(x), round(y), f)

    for y in range(0, HEIGHT):
        write_point(n, round(WIDTH / 2) + 1, round(y), f)

    f.close()


def spiral():
    n = init_n()

    f = open("spiral.txt", "w")
    f.write('0.2 0.1 0.8\n')

    for x in range(round(WIDTH / 2) - 1, round(WIDTH / 2) + 2):
        for y in range(int(HEIGHT / 3), int(2 * HEIGHT / 3)):
            write_point(n, round(x), round(y), f)

    for y in range(int(HEIGHT / 3), int(2 * HEIGHT / 3)):
        write_point(n, round(WIDTH / 2) + 1, round(y), f)

    f.close()


def read_stats():
    f = open("stats.txt", "r")

    count = 0
    x = list()
    y1 = list()
    y2 = list()

    line = f.readline()
    while line:
        count += 1
        x.append(count)
        y1.append(line.split()[0])
        y2.append(line.split()[1])
        line = f.readline()

    f.close()

    f = open("x.txt", "w")
    for i in x:
        f.write(str(i) + '\n')
    f.close()

    f = open("y1.txt", "w")
    for i in y1:
        f.write(str(i) + '\n')
    f.close()

    f = open("y2.txt", "w")
    for i in y2:
        f.write(str(i) + '\n')
    f.close()


if __name__ == '__main__':
    rule_1()
    rule_2()
    blob()
    chase()
    wave()
    spiral()

    read_stats()
