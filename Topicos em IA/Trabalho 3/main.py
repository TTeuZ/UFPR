from tools.reader import read_problem
import argparse

def main(args):
    problem = read_problem(args.path)

    print(problem._variables)

    for constraint in problem._constraints:
        print(constraint._type)
        print(constraint._scope)
        print(constraint._tuples)

    # solver = csp_solver()
    # result = solver(problem)

    # write_result(result)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="CSP Solver", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument("--path", "-p", type=str, required=True)

    main(parser.parse_args())