#!/usr/bin/env python3

import click

@click.command()
@click.option("--count", default=1, help="Number of repetitions.")
@click.option("--value", prompt="Value to repreat",
              help="The value to repeat.")
def repeat(count, value):
    """Simple program that repeats 'value' for a total of 'count' times."""
    for idx in range(count):
        click.echo("%3d: %s" % (idx, value))

if __name__ == '__main__':
    repeat()

