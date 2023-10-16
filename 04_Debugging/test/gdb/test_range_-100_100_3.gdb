set pagination off

set $n_elemnt = 0

break range_get if ($n_elemnt++ >= 27 && $n_elemnt < 36)
    command 1
    echo @@@
    printf "%d %d %d %d\n", i.start, i.stop, i.step, i._current
    continue
end

run -100 100 3 > /dev/null

quit
