sleeptime=28800

for target in 706302984098958615887419482678363257328890980413357843758051278703714 \
                682299972541136472468385275199326027894632614812228285111228659757941 \
                683138016631375037955555735732188269151122200946135643617048601445752 \

do
    start_time=$(date +%s)
    ./howgT $target 24 31 &
    pid=$(ps -ef | grep "howgT" | grep -v grep | awk '{print $2}')

    sleep $sleeptime
    end_time=$(date +%s)
    cost_time=$[ $end_time-$start_time ]
    echo $cost_time

    if [ $cost_time -gt $sleeptime ]
    then
    echo "out of time"
    kill -9 $pid
    echo "kill"
    fi
done



