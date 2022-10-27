res = "insert into join_table_large_4 values"

for i in range(11, 30):
    res += "(" + str(i) + "," + str(i) + "),"

print(res)