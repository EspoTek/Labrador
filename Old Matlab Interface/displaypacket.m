function [] = displaypacket(new_packets)

global saved_waveform_ch1
global saved_waveform_ch2
global scope_mode
global gui_scope_running
global fastmode


%Keep the arrays small(ish)
if length(saved_waveform_ch1)>3.75e6/(16*fastmode)
    saved_waveform_ch1 = saved_waveform_ch1(length(saved_waveform_ch1)-3.75e6/(16*fastmode):end);
end
if length(saved_waveform_ch2)>1e6
    saved_waveform_ch2 = saved_waveform_ch2(length(saved_waveform_ch2)-1e6:end);
end



%%Insta-return if scope is paused
if(~gui_scope_running)
    return
end

%%Exception for mode 6
if (scope_mode == 6)
    transfer_contents_temp = [];
    for tempovar = 0:length(new_packets)/750 - 1
        transfer_contents_temp = [transfer_contents_temp new_packets((tempovar*750+1):(tempovar*750+748))];
    end
    saved_waveform_ch1 = [saved_waveform_ch1 transfer_contents_temp];
    return
end

%%Exception for mode 7
if (scope_mode == 7) 
    new_packets = double(new_packets);     
    
    topbytes = new_packets(~logical(mod(1:length(new_packets),2)));
    botbytes = new_packets(logical(mod(1:length(new_packets),2)));
    
    botbytes = sign(topbytes) .* abs(botbytes); %lower bytes should steal sign info from top byte

    realval = topbytes*16 + botbytes/16; 
       
    transfer_contents_temp = [];
    for tempovar = 0:length(realval)/375 - 1
        transfer_contents_temp = [transfer_contents_temp realval((tempovar*375+1):(3*fastmode+1):(tempovar*375+374))];
    end
    saved_waveform_ch1 = [saved_waveform_ch1 transfer_contents_temp];
    return
end


%%Pull out CH1 data
if scope_mode < 5
    transfer_contents_temp = [];
    for tempovar = 0:length(new_packets)/750 - 1
        transfer_contents_temp = [transfer_contents_temp new_packets((tempovar*750+1):(tempovar*750+374))];
    end
    saved_waveform_ch1 = [saved_waveform_ch1 transfer_contents_temp];
end

%%Pull out CH2 data for relevant states
if (scope_mode == 1 | scope_mode == 2 | scope_mode == 4)
    transfer_contents_temp = [];
    for tempovar = 0:length(new_packets)/750 - 1
        transfer_contents_temp = [transfer_contents_temp new_packets((tempovar*750+376):(tempovar*750+748))];
    end
    saved_waveform_ch2 = [saved_waveform_ch2 transfer_contents_temp];
end

%     transfer_contents_whole = [transfer_contents_0 transfer_contents_1]
%         transfer_contents_temp = [];
%     for tempovar = 0:length(transfer_contents_whole)/750 - 1
%         transfer_contents_temp = [transfer_contents_temp transfer_contents_whole((tempovar*750+1):(tempovar*750+748))];
%     end
%     plot(transfer_contents_temp)
