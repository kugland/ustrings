# ustrings

A UTF-8 aware version of the `strings` utility.

Similar to the standard `strings` command, `ustrings` extracts and displays
readable text from binary files. However, unlike `strings` which only outputs
ASCII characters, `ustrings` properly handles and outputs any valid UTF-8
encoded text.

## Usage

```bash
./ustrings < binary_file
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
