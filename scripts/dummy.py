res = "insert into join_table_large_6 values"

for i in range(90, 101):
    res += "(" + str(i) + "," + str(i) + "),"

print(res)