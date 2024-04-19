from tools.csp_solver import csp_solver
from tools.utils import read_problem, write_result
import argparse

def main(args):
    problem = read_problem(args.path)

    solver = csp_solver()
    result = solver.solve(problem)

    write_result(result)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="CSP Solver", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument("--path", "-p", type=str, required=True)

    main(parser.parse_args())