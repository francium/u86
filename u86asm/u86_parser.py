# PEP-563
from __future__ import annotations

from dataclasses import dataclass
from enum import Enum
from typing import List, Union, Tuple

from result import Result, Ok, Err

from u86_tokenizer import Tokenizer, TokenType, Token


class NodeType(Enum):
    PROG = 1  # Program
    INS_LN = 2  # Instruction line
    MNE = 3  # Mnemonic
    REG_EXPR = 4  # Register expression
    IMM = 5  # Immediate value


@dataclass
class ASTNode:
    kind: NodeType
    value: Union[List[ASTNode], str]


class Parser:
    def __init__(self, tkzr: Tokenizer):
        self._stream = tkzr.stream()
        self._ast: ASTNode = ASTNode(NodeType.PROG, [])

    def parse(self) -> Result[Tuple[Token, str], bool]:
        tk = next(self._stream)
        while tk.kind != TokenType.EOF:
            r_expect = self._expect(TokenType.MNE, tk)
            if r_expect.err():
                return r_expect

            tk = next(self._stream)

        return Ok()

    def _expect(
        self, expected: TokenType, tk: Token
    ) -> Result[Tuple[Token, str], bool]:
        if tk.kind != expected:
            return Err((tk, f'Expected {expected}, but got {tk.kind}: "{tk.value}"'))

        return Ok()
        #  if expected == TokenType.LF:
        #      ...
        #  elif expected == TokenType.MNE:
        #      ...
        #  elif expected == TokenType.ARG:
        #      ...
        #  elif expected == TokenType.SPC:
        #      ...
        #  elif expected == TokenType.EOF:
        #      ...
        #  elif expected == TokenType.LABEL:
        #      ...
        #  else:
        #      ...
        #

    def _get_trace(self):
        ...
