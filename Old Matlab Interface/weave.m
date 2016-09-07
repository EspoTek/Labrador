    transfer_contents_temp = [];
    for tempovar = 0:length(transfer_contents_0)/750 - 1
        transfer_contents_temp = [transfer_contents_temp transfer_contents_0((tempovar*750+1):(tempovar*750+375))];
        transfer_contents_temp = [transfer_contents_temp transfer_contents_1((tempovar*750+1):(tempovar*750+375))];
    end
    
    plot(transfer_contents_temp)