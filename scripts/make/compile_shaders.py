import os

def preprocess_shader(input_file, output_file, include_path):
    with open(input_file, 'r') as infile:
        lines = infile.readlines()

    with open(output_file, 'w') as outfile:
        lines_count = sum(1 for line in lines if line.strip().startswith("#include"))

        i = 0
        for line in lines:
            if line.strip().startswith("#include"):
                i += 1
                include_file = line.strip().split('"')[1]
                print(f"\033[1;0m * \033[1;31mCompiling: \033[1;0m{include_file}", end="")
                print(f" \033[1;32m[{i}/{lines_count}]\033[0m")
                include_full_path = os.path.join(include_path, include_file)
                if os.path.exists(include_full_path):
                    with open(include_full_path, 'r') as incfile:
                        outfile.write(incfile.read())
                        outfile.write("\n")
                else:
                    raise FileNotFoundError(f"Included file {include_file} not found.")
            else:
                outfile.write(line)

preprocess_shader("./shaders/main.glsl", "./shaders/compiled_shader.glsl", "./shaders/")
