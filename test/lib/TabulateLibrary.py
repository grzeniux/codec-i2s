from robot.api.deco import keyword, library
from robot.libraries.BuiltIn import BuiltIn
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
        table = tabulate(rows, headers=["#", "Expected", "Actual", "Match"], tablefmt="html")
        BuiltIn().log(table, html=True)

    @keyword("Should Match Titles")
    def should_match_titles(self, expected, actual):
        rows = []
        all_match = True
        for idx, exp in enumerate(expected):
            act = actual[idx] if idx < len(actual) else "<brak>"
            match = "✓" if exp == act else "✗"
            if match == "✗":
                all_match = False
            rows.append([idx + 1, exp, act, match])
        table = tabulate(rows, headers=["#", "Expected", "Actual", "Match"], tablefmt="html")
        BuiltIn().log(table, html=True)
        if not all_match:
            raise AssertionError("Tytuły piosenek nie zgadzają się — sprawdź tabelę powyżej.")
