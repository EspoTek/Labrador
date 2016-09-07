function timer_strap(t_handle, desired_per)
% %Function timer_strap(), by Christopher Paul Esposito ("Esposch")
% %Make sure you call this during every timer callback, and set the timer's "ExecutionMode" to "FixedRate".
% %Takes timer object t_handle and uses negative feedback to bring the steady state period of t_handle towards desired_per.
% %This means that your code will become CPU-independent, as queuing delay won't affect the period.
% %It will not, however, perfectly account for random variance in delay due to a varying CPU load.
% 
% n = 500; %Times between resetting.  Higher n means more accuracy (the period between the nth and n+1th execution is not considered!), but also less able to cope with a varying load.  Oddly, errors seem to show in realtime application with low n.
% kp = 0.1;  %Proportional gain. Well, not really.  But it basically works the same way.  Research "PID Controllers" to understand how this works (moral of the story: smaller kp prevents indefinite oscillation, but means it takes longer to reach steady state.  Above a certain threshold kp, the whole system will diverge and fail).  
% real_per = get(t_handle, 'AveragePeriod');  %%Actual (average) time between runs (in real seconds).
% if (get(t_handle, 'TasksExecuted') < n)
%     return;
% end    
% reference_per = get(t_handle, 'Period');  %%What Matlab has set the period to.
% reference_per = reference_per - kp*(real_per - desired_per);  %%Subtracting off the error; negative feedback!
% 
% stop(t_handle);  %Need to reset everything to write the new period.  This means that the last window of data is gone!
% set(t_handle, 'Period', reference_per);
% start(t_handle);

global extra_goes;
tasks_exec = get(t_handle, 'TasksExecuted') + extra_goes;
average_per = get(t_handle, 'AveragePeriod') * (get(t_handle, 'TasksExecuted') / tasks_exec);

behind = (average_per - desired_per) * tasks_exec;
if behind>desired_per
    global sem_avail
    sem_avail = sem_avail + 1;
    extra_goes = extra_goes + 1;
end
    
