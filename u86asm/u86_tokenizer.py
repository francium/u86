from enum import Enum
from typing import cast, Optional, Tuple, Iterator
from dataclasses import dataclass

from result import Result, Ok, Err

from u86_instructions import INSTRUCTIONS


class TokenType(Enum):
    LF = 0  # Line feed
    MNE = 1  # Keyword
    ARG = 2  # Argument
    SPC = 3  # Space/tab
    EOF = 4  # End of file
    LABEL = 5  # Label


@dataclass
class Token:
    kind: TokenType
    value: str
    position: int
    line: int


class Tokenizer:
    def __init__(self, src: str):
        self._src = src
        self._index = 0
        self._cur_line = 1

    def stream(self) -> Iterator[Token]:
        return self.__iter__()

    def __iter__(self) -> Iterator[Token]:
        while True:
            token = self._get_token()
            yield token
            if token.kind == TokenType.EOF:
                break

    def _get_token(self) -> Token:
        c = self._peek_ch()
        if self._is_eof(c):
            return self._get_eof()
        elif self._is_space(c):
            return self._get_whitespace()
        elif self._is_lf(c):
            return self._get_lf()
        else:
            return self._get_keyword_or_expression()

    def _get_eof(self) -> Token:
        return Token(TokenType.EOF, "", -1, self._cur_line)

    def _get_whitespace(self) -> Token:
        c, i = cast(Tuple[str, int], self._get_ch())
        self._skip_whitespaces()
        return Token(TokenType.SPC, c, i, self._cur_line)

    def _get_lf(self) -> Token:
        c, i = cast(Tuple[str, int], self._get_ch())
        return Token(TokenType.LF, c, i, self._cur_line)

    def _get_keyword_or_expression(self) -> Token:
        buf = ""
        start_index = -1

        while self._is_non_whitespace(self._peek_ch()):
            c, i = cast(Tuple[str, int], self._get_ch())
            if start_index is None:
                start_index = i
            buf += c

        if self._is_kw(buf):
            tt = TokenType.MNE
        elif self._is_label(buf):
            tt = TokenType.LABEL
            buf = buf[:-1]  # trim colon
        else:
            tt = TokenType.ARG

        return Token(tt, buf, start_index, self._cur_line)

    def _peek_ch(self) -> Optional[str]:
        if 0 <= self._index < len(self._src):
            return self._src[self._index]
        return None

    def _get_ch(self) -> Tuple[Optional[str], int]:
        if 0 <= self._index < len(self._src):
            c = self._src[self._index]
            i = self._index
            self._index += 1

            if self._is_lf(c):
                self._cur_line += 1

            return cast(Tuple[str, int], (c, i))
        return None, -1

    def _unget_ch(self):
        if 0 < self._index <= len(self._src) - 1:
            self._index -= 1

            if self._is_lf(self._src[self._index]):
                self._cur_line -= 1

    def _skip_whitespaces(self) -> None:
        while self._is_space(self._peek_ch()):
            self._get_ch()

    @classmethod
    def _is_label(cls, word: str) -> bool:
        return word[-1] == ":"

    @classmethod
    def _is_kw(cls, word: str) -> bool:
        return word.lower() in INSTRUCTIONS

    @classmethod
    def _is_non_whitespace(cls, c: Optional[str]) -> bool:
        return not cls._is_space(c) and not cls._is_lf(c) and not cls._is_eof(c)

    @classmethod
    def _is_space(cls, c: Optional[str]) -> bool:
        return c in [" ", "\t"]

    @classmethod
    def _is_lf(cls, c: Optional[str]) -> bool:
        return c == "\n"

    @classmethod
    def _is_eof(cls, c: Optional[str]) -> bool:
        return c is None
