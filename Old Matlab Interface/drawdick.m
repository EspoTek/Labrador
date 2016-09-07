x = -21:20
leftBall = sqrt(21.^2 - x.^2)
rightBall = fliplr(leftBall)
x = -21:0

length = 156
leftCockHalf = sqrt(21.^2 - x.^2) + length
centreDip = length + 21/2
rightCockHalf = fliplr(leftCockHalf)

penis = [leftCockHalf centreDip rightCockHalf]

cockAndBalls = [leftBall penis rightBall]

plot(cockAndBalls)
diff = (length + 21 - 128)/2
axis([-diff, 128 + diff, 0, length + 21])

cockAndBalls = cockAndBalls * 255/max(cockAndBalls)
cockAndBalls = uint8(cockAndBalls)

for i=1:128
    fprintf('%d\t', cockAndBalls(i))
end

% length = 156
% plot([sqrt(21.^2 - [-21:20].^2), [sqrt(21.^2 - [-21:0].^2) + 156, 156 + 21/2, fliplr(sqrt(21.^2 - [-21:0].^2)+156)] fliplr(sqrt(21.^2 - [-21:20].^2))])
% axis([-(156+21-128)/2, 128 + (156+21-128)/2, 0, length + 21])
