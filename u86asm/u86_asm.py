#!/bin/env python3

from typing import List
from sys import argv

from result import Result, Ok, Err

from u86_tokenizer import Tokenizer


def main(argv: List[str]) -> int:
    args_ok = _validate_argv(argv)
    if args_ok.is_err():
        print(args_ok.err())
        return 1

    fname = argv[1]
    try:
        with open(fname, "r") as fin:
            src = fin.read()
    except Exception as err:
        print("File IO error:", err)
        return 1

    tkzr = Tokenizer(src)
    for (token_type, token) in tkzr:
        print(token_type, token)

    return 0


def _validate_argv(argv: List[str]) -> Result[str, bool]:
    if len(argv) != 2:
        return Err("Invalid arguments")

    return Ok()


if __name__ == "__main__":
    main(argv)
