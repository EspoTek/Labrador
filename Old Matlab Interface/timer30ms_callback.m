global sem_avail
sem_avail = sem_avail + 1;
timer_strap(timer_30ms, 30e-3);
%get(timer_30ms, 'AveragePeriod');
%get(timer_30ms, 'Period');