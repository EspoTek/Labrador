global gui_axes

tic
for n = 1:10
    plot(gui_axes, 1, 1)
    drawnow
end
toc