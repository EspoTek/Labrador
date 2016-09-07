function gain = autogain(minrail, maxrail)
vcc = 3.3
r1 = 1000
r2 = 75

maxgain = vcc / (2 * (maxrail - vcc/2) * r2/(r1+r2))
mingain = vcc / (2 * (minrail - vcc/2) * r2/(r1+r2))

maxgain = min(abs(mingain) * 0.9, abs(maxgain) * 0.9)

for snap = [64 32 16 8 4 2 1 0.5]
    if maxgain>snap
        gain = snap
        break
    end
end
