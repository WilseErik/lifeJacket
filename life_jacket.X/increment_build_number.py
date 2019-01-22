if __name__ == "__main__":
    with open("inc/build_number.h") as src_file:
            lines = src_file.readlines()

    current_version = int(lines[0].split('"')[1])

    with open("inc/build_number.h", 'w') as f:
        print('#define BUILD_NUMBER_STRING "' + str(current_version + 1) + '"\r\n', file=f)

    print(current_version)
    print("Build number incremented")