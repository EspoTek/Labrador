if libk_error
    dropped_packets = dropped_packets + 1;
    if (dropped_packets > 10)
        break
        %resynchronise
        %dropped_packets = 0;
        %waveform_exists = 0;
    end
else
    dropped_packets = 4*dropped_packets/5;
end