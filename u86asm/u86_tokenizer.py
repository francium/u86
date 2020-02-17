from enum import Enum
from typing import cast, Optional, Tuple

from result import Result, Ok, Err

from u86_instructions import INSTRUCTIONS


class TokenType(Enum):
    LF = 0  # Line feed
    KW = 1  # Keyword
    ARG = 2  # Argument
    SPC = 3  # Space/tab
    EOF = 4  # End of file
    LABEL = 5  # Label


class Tokenizer:
    def __init__(self, src: str):
        self._src = src
        self._index = 0

    def __iter__(self):
        while True:
            token_type, token = self._get_token()
            yield token_type, token
            if token_type is TokenType.EOF:
                break

    def _get_token(self) -> Tuple[TokenType, str]:
        c = self._peek_ch()
        if self._is_eof(c):
            return self._get_eof()
        elif self._is_space(c):
            return self._get_whitespace()
        elif self._is_lf(c):
            return self._get_lf()
        else:
            return self._get_keyword_or_expression()

    def _get_eof(self) -> Tuple[TokenType, str]:
        return TokenType.EOF, ''

    def _get_whitespace(self) -> Tuple[TokenType, str]:
        self._swollow_whitespaces()
        return TokenType.SPC, " "

    def _get_lf(self) -> Tuple[TokenType, str]:
        self._get_ch()
        return TokenType.LF, "\n"

    def _get_keyword_or_expression(self) -> Tuple[TokenType, str]:
        buf = ""
        while self._is_non_whitespace(self._peek_ch()):
            buf += cast(str, self._get_ch())

        if self._is_kw(buf):
            tt = TokenType.KW
        elif self._is_label(buf):
            tt = TokenType.LABEL
            buf = buf[:-1] # trim colon
        else:
            tt = TokenType.ARG

        return tt, buf

    def _peek_ch(self) -> Optional[str]:
        if 0 <= self._index < len(self._src):
            return self._src[self._index]
        return None

    def _get_ch(self) -> Optional[str]:
        if 0 <= self._index < len(self._src):
            c = self._src[self._index]
            self._index += 1
            return c
        return None

    def _unget_ch(self):
        if 0 < self._index <= len(self._src) - 1:
            self._index -= 1

    def _swollow_whitespaces(self) -> None:
        while True:
            c = self._get_ch()
            if c == None or c not in [" ", "\t"]:
                self._unget_ch()
                return

    @classmethod
    def _is_label(cls, word: str) -> bool:
        return word[-1] == ":"

    @classmethod
    def _is_kw(cls, word: str) -> bool:
        return word in INSTRUCTIONS

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
