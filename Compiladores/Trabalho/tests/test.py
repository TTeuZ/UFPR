import subprocess
import os

root_path = "/home/tteuz/Desktop/UFPR/Compiladores/Trabalho/tests"
tests = [
    (f"{root_path}/test0", True), (f"{root_path}/test1", True), (f"{root_path}/test2", True), (f"{root_path}/test3", False),
    (f"{root_path}/test4", True), (f"{root_path}/test5", False), (f"{root_path}/test6", False), (f"{root_path}/test7", True),
    (f"{root_path}/test8", True), (f"{root_path}/test9", True), (f"{root_path}/test10", True), (f"{root_path}/test11", True),
    (f"{root_path}/test12", True), (f"{root_path}/test13", True), (f"{root_path}/test14", True), (f"{root_path}/test16", True),
    (f"{root_path}/test17", False), (f"{root_path}/test18", False), (f"{root_path}/test19", True), (f"{root_path}/test20", True),
    (f"{root_path}/test21", False), (f"{root_path}/test22", True), (f"{root_path}/test23", False), (f"{root_path}/test24", True),
    (f"{root_path}/test25", True), (f"{root_path}/test26", True), (f"{root_path}/test27", True), (f"{root_path}/test28", True),
]

failed_tests = []

for test in tests:
    test_path, test_result  = test[0], test[1]

    test_name = os.path.basename(test_path)
    pas_file = f"{test_path}/{test_name}.pas"
    mepa_file = f"{test_path}/{test_name}.mepa"

    compiler_cmd = f"./compiler {pas_file}"
    diff_cmd = f"diff MEPA {mepa_file}"

    print(f"Executing: {compiler_cmd}")
    exc_result = subprocess.run(compiler_cmd, shell=True).returncode == 0
    diff_result = subprocess.run(diff_cmd, shell=True).returncode != 0

    if exc_result != test_result or diff_result:
        failed_tests.append(test)

print("############################################################\n")

if len(failed_tests) != 0:
    print("Execution failed!\n")
    for test in failed_tests:
        test_path  = test[0]
        test_name = os.path.basename(test_path)
        print(f" - ${test_name}\n")
else:
    print("Executiopn success - All tests passed!\n")

subprocess.run(f"rm MEPA", shell=True)
print("############################################################\n")