from robot.api.deco import keyword, library
from tabulate import tabulate

@library(scope='GLOBAL')
class TabulateLibrary:

    @keyword("Print Song Table")
    def print_song_table(self, expected, actual):
        rows = []
        for idx, exp in enumerate(expected):
            act = actual[idx] if idx < len(actual) else "<brak>"
            match = "✓" if exp == act else "✗"
            rows.append([idx + 1, exp, act, match])
        print(tabulate(rows, headers=["#", "Expected", "Actual", "Match"], tablefmt="grid"))
