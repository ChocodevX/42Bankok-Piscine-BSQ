#!/usr/bin/env python3
"""
BSQ test case generator.
Format: <rows><empty><obstacle><full>\n followed by rows x cols grid.
"""

import random
import argparse
import os
import sys


def generate_map(
    rows: int,
    cols: int,
    obstacle_density: float = 0.1,
    empty_char: str = ".",
    obstacle_char: str = "o",
    full_char: str = "x",
) -> str:
    lines = [f"{rows}{empty_char}{obstacle_char}{full_char}"]
    for _ in range(rows):
        row = ""
        for _ in range(cols):
            row += obstacle_char if random.random() < obstacle_density else empty_char
        lines.append(row)
    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser(description="BSQ test case generator")
    parser.add_argument("--rows", type=int, default=10, help="Number of rows")
    parser.add_argument("--cols", type=int, default=10, help="Number of columns")
    parser.add_argument(
        "--density",
        type=float,
        default=0.1,
        help="Obstacle density 0.0–1.0 (default 0.1)",
    )
    parser.add_argument(
        "--empty", type=str, default=".", help="Empty cell character (default '.')"
    )
    parser.add_argument(
        "--obstacle", type=str, default="o", help="Obstacle character (default 'o')"
    )
    parser.add_argument(
        "--full", type=str, default="x", help="Full/solution character (default 'x')"
    )
    parser.add_argument(
        "--seed", type=int, default=None, help="Random seed for reproducibility"
    )
    parser.add_argument(
        "--count", type=int, default=1, help="Number of test files to generate"
    )
    parser.add_argument(
        "--outdir",
        type=str,
        default=".",
        help="Output directory (default: current dir)",
    )
    parser.add_argument(
        "--prefix",
        type=str,
        default="testcase",
        help="Output filename prefix (default: 'testcase')",
    )
    parser.add_argument(
        "--stdout",
        action="store_true",
        help="Print to stdout instead of writing files",
    )
    parser.add_argument(
        "--all-obstacles",
        action="store_true",
        help="Fill the entire map with obstacles (edge case)",
    )
    parser.add_argument(
        "--no-obstacles",
        action="store_true",
        help="Generate a clean map with zero obstacles (edge case)",
    )

    args = parser.parse_args()

    # Validate characters
    for name, ch in [("empty", args.empty), ("obstacle", args.obstacle), ("full", args.full)]:
        if len(ch) != 1:
            print(f"Error: --{name} must be exactly one character", file=sys.stderr)
            sys.exit(1)
        if not (32 <= ord(ch) <= 126):
            print(f"Error: --{name} must be a printable ASCII character", file=sys.stderr)
            sys.exit(1)
    if len({args.empty, args.obstacle, args.full}) != 3:
        print("Error: --empty, --obstacle, and --full must all be different characters", file=sys.stderr)
        sys.exit(1)

    if args.seed is not None:
        random.seed(args.seed)

    density = args.density
    if args.all_obstacles:
        density = 1.0
    elif args.no_obstacles:
        density = 0.0

    os.makedirs(args.outdir, exist_ok=True)

    for i in range(args.count):
        content = generate_map(
            rows=args.rows,
            cols=args.cols,
            obstacle_density=density,
            empty_char=args.empty,
            obstacle_char=args.obstacle,
            full_char=args.full,
        )
        if args.stdout:
            print(content)
            if i < args.count - 1:
                print()
        else:
            filename = (
                f"{args.prefix}_{i + 1}.txt" if args.count > 1 else f"{args.prefix}.txt"
            )
            path = os.path.join(args.outdir, filename)
            with open(path, "w") as f:
                f.write(content)
            print(f"Written: {path}")


if __name__ == "__main__":
    main()
