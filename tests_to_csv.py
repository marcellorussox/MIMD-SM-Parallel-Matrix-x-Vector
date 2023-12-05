import os
import csv
import re

def extract_out_data(file_path):
    with open(file_path, 'r') as file:
        content = file.read()

    match_header = re.match(r'<============== TEST (\d+) x (\d+) ==============>', content)
    if not match_header:
        return None

    rows, columns = map(int, match_header.groups())

    pattern = r'(.*?Overall time: (\d+\.\d+))'
    matches = list(re.finditer(pattern, content, re.DOTALL))

    data = []
    i = 0
    for match in matches:
        i += 1
        test_times = [float(group) for group in match.groups()[1::2]]
        for num_test, time in enumerate(test_times, start=1):
            data.append((rows, columns, (i - 1) // 5 + 1, time))

    return data

def process_directory(directory_path):
    out_file_path = os.path.join(directory_path, 'pdc2.out')

    out_data = extract_out_data(out_file_path)

    return out_data

def main(input_directory, output_csv):
    all_data = []

    for subdir in os.listdir(input_directory):
        subdir_path = os.path.join(input_directory, subdir)
        if os.path.isdir(subdir_path):
            out_data = process_directory(subdir_path)

            if out_data is not None:
                all_data.extend(out_data)

    with open(output_csv, 'w', newline='') as csv_file:
        csv_writer = csv.writer(csv_file)
        csv_writer.writerow(['rows', 'columns', 'threads', 'test', 'time'])
        csv_writer.writerows(all_data)

    print(f"I dati sono stati esportati con successo nel file CSV: {output_csv}")

# Esempio di utilizzo
main('test', 'data.csv')
