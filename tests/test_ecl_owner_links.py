"""ECL consumers must resolve to the same accepted owner as their definition."""
from pathlib import Path
import re
import tomllib
import unittest

ROOT = Path(__file__).resolve().parents[1]


class EclOwnerLinksTests(unittest.TestCase):
    def test_known_ecl_definitions_and_consumers_agree(self):
        units = tomllib.loads((ROOT / "config/match-units.toml").read_text())["units"]
        # Compiler-local symbols, library copies and folds across different
        # production types are outside this bounded semantic-owner check.
        owner = re.compile(r"^(?:\?[^@]+@|\?\?[01])(?:EclManager|EclRuntime|ScriptStack)@th20@@")
        definitions = {}
        for key, unit in units.items():
            symbol = unit["symbol"]
            if owner.match(symbol):
                definitions.setdefault(symbol, set()).add(unit["target_address"])
        checked = set()
        for key, unit in units.items():
            for relocation in unit.get("relocations", []):
                symbol = relocation["symbol"]
                if symbol in definitions:
                    self.assertIn(relocation["target"], definitions[symbol],
                                  f"{key} calls a different owner for {symbol}")
                    checked.add(symbol)
        self.assertIn("?invalidate_async@EclManager@th20@@QAEXXZ", checked)
        self.assertIn("?terminate_async@EclManager@th20@@QAEXXZ", checked)
        self.assertNotEqual(definitions["?invalidate_async@EclManager@th20@@QAEXXZ"],
                            definitions["?terminate_async@EclManager@th20@@QAEXXZ"])
