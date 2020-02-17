from u86_tokenizer import TokenType, Tokenizer


SAMPLE_ASM = """\
mov r1 2
mov r2 3
mul r1 r2
hlt

foobar:
mov r1 [r1+3]
"""

EXPECTED_TOKEN_STREAM = [
    (TokenType.ARG, 'mov'),
    (TokenType.SPC, ' '),
    (TokenType.ARG, 'r1'),
    (TokenType.SPC, ' '),
    (TokenType.ARG, '2'),
    (TokenType.LF, '\n'),
    (TokenType.ARG, 'mov'),
    (TokenType.SPC, ' '),
    (TokenType.ARG, 'r2'),
    (TokenType.SPC, ' '),
    (TokenType.ARG, '3'),
    (TokenType.LF, '\n'),
    (TokenType.KW, 'mul'),
    (TokenType.SPC, ' '),
    (TokenType.ARG, 'r1'),
    (TokenType.SPC, ' '),
    (TokenType.ARG, 'r2'),
    (TokenType.LF, '\n'),
    (TokenType.KW, 'hlt'),
    (TokenType.LF, '\n'),
    (TokenType.LF, '\n'),
    (TokenType.LABEL, 'foobar'),
    (TokenType.LF, '\n'),
    (TokenType.ARG, 'mov'),
    (TokenType.SPC, ' '),
    (TokenType.ARG, 'r1'),
    (TokenType.SPC, ' '),
    (TokenType.ARG, '[r1+3]'),
    (TokenType.LF, '\n'),
    (TokenType.EOF, ''),
]


def test_token_stream():
    tkzer = Tokenizer(SAMPLE_ASM)
    stream_len = range(len(EXPECTED_TOKEN_STREAM))
    zipped = zip(stream_len, EXPECTED_TOKEN_STREAM, tkzer)
    for (num, expected, actual) in zipped:
        assert f'token #{num}' and expected == actual
