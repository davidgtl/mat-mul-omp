#!/usr/bin/env python3
import time
import subprocess
import argparse
from matplotlib import pyplot as plt


def timeexe(path, threads, size):
    start = time.time()
    # time.sleep(0.1)
    subprocess.run([f"{path}", str(threads), str(size)])
    end = time.time()
    return float(end - start)


def make_plot(table):
    fig = plt.figure()

    lines = []
    for t in table:
        line, = plt.plot(t["problem size"], t["time"], label=t["name"])
        lines.append(line)

    plt.xlabel('Problem size', fontsize=18)
    plt.ylabel('Time[s]', fontsize=16)
    fig.legend(handles=lines)
    fig.show()

    fig.savefig("stats.png")


def run_tests(executable_path, threads, psizes, runs):
    table = []
    print("Running tests: ")

    for t in threads:
        times = []
        for s in psizes:
            print(f"threads: {t}, problem size: {s}")
            avg = 0.0
            for r in range(runs):
                dt = timeexe(executable_path, t, s)
                print(f"run {r}: {dt}ms")
                avg += dt
            if runs > 1:
                avg /= runs
                print(f"average time: {avg}s")
            print("")
            times.append(avg)
        print("")
        print("")
        table.append({"name": f"threads_{t}", "problem size": psizes, "time": times})
    return table


def main():
    parser = argparse.ArgumentParser(prog='python perf.py', description='Autorun program with parameters and create '
                                                                        'performance graph and table. please provide -t '
                                                                        'and one of -s or  -r')
    parser.add_argument('executable_path', type=str, help='The path to the executable you want to time, '
                                                          'it must accept 2 parameters: thread_num and '
                                                          'problem_size')
    parser.add_argument('-t', '--threads', nargs='+', type=int, help='A list of thread numbers')
    parser.add_argument('-s', '--sizes', nargs='+', type=int, help='A list of problem sizes')
    parser.add_argument('-sr', '--range', nargs='+', type=int,
                        help='3 numbers signifying start step end of the problem sizes')
    parser.add_argument('-r', '--runs', nargs='?', type=int, default=1, help='How many times to sample tests')

    args = parser.parse_args()

    print(args)

    if args.sizes is not None:
        psizes = args.sizes
    elif args.range is not None:
        psizes = range(args.range[0], args.range[1] + 1, args.range[2])
    else:
        print("Please provise a range or a list of problem sizes")

    if args.threads is not None:
        threads = args.threads
    else:
        print("Please provise a range or a list of problem sizes")

    table = run_tests(args.executable_path, threads, psizes, args.runs)
    make_plot(table)


if __name__ == "__main__":
    main()
