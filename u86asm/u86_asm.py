#!/bin/env python3

from typing import List
from sys import argv

from result import Result, Ok, Err

from u86_tokenizer import Tokenizer
from u86_parser import Parser
from u86_trace import get_trace


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
    parser = Parser(tkzr)

    r_parse = parser.parse()
    if r_parse.is_err():
        print(get_trace(src, *r_parse.err()))
        return 1

    return 0


def _validate_argv(argv: List[str]) -> Result[str, bool]:
    if len(argv) != 2:
        return Err("Invalid arguments")

    return Ok()


if __name__ == "__main__":
    main(argv)
