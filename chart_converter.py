BPM = 135
DURATION = 200
RESOLUTION = 192
# OFFSET = 17.75
OFFSET = 12

print(BPM)
print(DURATION)

n = int(input())
for i in range(n):
    note_in = input().split()
    if int(note_in[3]) > 4:
        continue
    if int(note_in[0]) >= 70656:
        tick = int(note_in[0])
        time = (70656 / BPM + (tick - 70656) / 120) * 60 / RESOLUTION  - OFFSET
    else:
        time = int(note_in[0]) * 60 / RESOLUTION / BPM - OFFSET
    print(note_in[3], f"{time:.2f}")
