set pagination off

break range_get if i._current % 5 == 0
    command 1
    echo @@@
    printf "%d %d %d %d\n", i.start, i.stop, i.step, i._current
    continue
end

run 1 12 > /dev/null

quit
