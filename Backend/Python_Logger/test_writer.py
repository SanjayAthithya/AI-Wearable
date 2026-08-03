from csv_writer import CSVWriter

# Create writer
writer = CSVWriter()

# Write header
writer.write_header([
    "Time",
    "IR",
    "RED"
])

# Write some sample rows
writer.write_row([1000, 65000, 80000])
writer.write_row([1001, 65100, 80100])
writer.write_row([1002, 65200, 80200])

# Save data
writer.flush()
writer.close()

print("===================================")
print("CSV Writer Test Successful")
print("===================================")

print("Samples :", writer.sample_count())
print("Filename:", writer.current_file())
print("Path    :", writer.current_path())