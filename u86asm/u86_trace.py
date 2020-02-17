from typing import Tuple

from u86_tokenizer import Token


def get_trace(src: str, token: Token, err_msg: str) -> str:
    rel_pos, line = _get_line_from_src(src, token.position)
    ln_fmt = str(token.line)
    ln_fmt_pad = " " * len(ln_fmt)
    return f"""\
Compiler Error:
{ln_fmt}    {line}
{ln_fmt_pad}    {_get_rel_pos_indicator(rel_pos)}
{err_msg}\
"""


def _get_line_from_src(src: str, index: int) -> Tuple[int, str]:
    start = 0
    end = len(src)
    for i in range(index, -1, -1):
        if src[i] == "\n":
            start = i + 1
            break

    for i in range(index, len(src)):
        if src[i] == "\n":
            end = i
            break

    return index - start, src[start:end]


def _get_rel_pos_indicator(pos: int) -> str:
    return (pos * " ") + "^"
