function output = sisprintf(value, unit, digits)
    %Catch for zero:
    if value == 0
        output = ['0' unit]
        return
    end
    positive = sign(value)
    value = value * sign(value)
    multi = floor(log10(value))
    mantissa = value / (10^(multi - mod(multi,3)))
    fmt = ['%' num2str(digits+4) '.' num2str(digits) 'f']
    numerals = sprintf(fmt, mantissa)
    
    
    switch(multi)
        case -12
            prefix = 'p';
        case -11
            prefix = 'p';
        case -10 
            prefix = 'p';
        case -9
            prefix = 'n';
        case -8
            prefix = 'n';
        case -7 
            prefix = 'n';
        case -6;
            prefix = 'u';
        case -5
            prefix = 'u';
        case -4
            prefix = 'u';
        case -3
            prefix = 'm';
        case -2
            prefix = 'm';
        case -1
            prefix = 'm';
        case 0
            prefix = '';
        case 1
            prefix = '';
        case 2
            prefix = '';
        case 3
            prefix = 'k';
        case 4
            prefix = 'k';
        case 5
            prefix = 'k';
        case 6
            prefix = 'M';
        case 7
            prefix = 'M';
        case 8
            prefix = 'M';
        case 9
            prefix = 'G';
        case 10
            prefix = 'G';
        case 11
            prefix = 'G';
        case 12
            prefix = 'T';
        case 13
            prefix = 'T';
        case 14
            prefix = 'T';
        otherwise
            error('Metric prefix not known')
    end
    
    %Searching for -ve includes the zero!
    if positive == -1
        sign_char = '-'
    else
        sign_char = ''
    end
    
    output = [numerals prefix unit];
    
            