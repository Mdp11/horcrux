# Horcrux

Program to encrypt and split a file into several "horcruxes" and to subsquently merge them and decrypt it.

### Usage

	horcrux create -n <number_of_horcruxes> <input_file> <output_folder>
	horcrux load -k <decryption_key> <input_file_1> ... <input_file_n> <output_file>


### Build

##### Dependencies:
- bazel 4.2.1
- gcc 9.3.0 (for linux build)
- mingw-w64 7.0.0 (for windows build)

The listed versions are guaranteed to work, but older versions may still work.

##### Linux executable build command:

    bazel build //main:horcrux_main

##### Windows executable build command:

    bazel build --config=w64 //main:horcrux_main 
