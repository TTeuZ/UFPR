import argparse

def write_clause(file, clause):
    clause_details = [int(elem) for elem in clause.strip().split()]
    clause_details.pop(-1)

    file.write("V\n")
    file.write(f"{len(clause_details)} {' '.join(str(abs(num)) for num in clause_details)}\n")
    file.write(f"1 {' '.join(str(int(num/(abs(num)))) for num in clause_details)}\n")


def write_domain(file, vars_qty):
    file.write(f"{vars_qty}\n")

    for _ in range(vars_qty):
        file.write("2 1 -1\n")


def skip_comments(file):
    all_skipped = False
    while not all_skipped:
        line = file.readline()
        if line[0] != "c": all_skipped = True

    return line


def main(args):
    with open(args.path, "r") as file:
        dimacs_header = skip_comments(file)
        header = [elem for elem in dimacs_header.strip().split()]
        vars_qty, clauses_qty = int(header[2]), int(header[3])

        with open("results.txt", "w") as result_file:
            write_domain(result_file, vars_qty)

            result_file.write(f"{clauses_qty}\n")
            for _ in range(clauses_qty):
                clause = file.readline()
                write_clause(result_file, clause)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="DIMACS to CSP file converter", formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument("--path", "-p", type=str, required=True)

    main(parser.parse_args())