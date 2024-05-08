BPM = 158
DURATION = 150
RESOLUTION = 192
OFFSET = -0.981012658227848

print(BPM)
print(DURATION)

n = int(input())
for i in range(n):
    note_in = input().split()
    if int(note_in[3]) > 4 or note_in[2] != 'N':
        continue
    time = int(note_in[0]) * 60 / RESOLUTION / BPM - OFFSET
    print(note_in[3], f"{time:.2f}")
