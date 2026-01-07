set N 20
set M 4

Matrix D $N $M
Vector y $N
Vector yhat $N
Vector res $N
Vector x $M

set A 0
set B 0
set names {}
for {set j 0} {$j < $M} {incr j} { lappend names P$j }
Matrix -names D $names

for {set i 0} {$i < $N} {incr i} {
    for {set j 0} {$j < $M} {incr j} {
	set D($i,$j) [random 6 1]
    }
    set val [expr 1 + 2*$D($i,0) + 3*$D($i,1) + 4*$D($i,2) + 5*$D($i,3)]
    if {$val < 90} {
	incr A
	set y($i) 1
    } else {
	incr B
	set y($i) -1
    }
}
puts "A=$A B=$B"
set r [svm -build D y yhat res]

set fp [open "| xgraph -M -bb -tk" w]

puts $fp "\n\"yorig\"\n"
for {set i 0} {$i < $N} {incr i} {
	puts $fp "$i $y($i)"
}

puts $fp "\n\"yhat\"\n"
for {set i 0} {$i < $N} {incr i} {
	puts $fp "$i $yhat($i)"
}

puts $fp "\n\"res\"\n"
for {set i 0} {$i < $N} {incr i} {
	puts $fp "$i $res($i)"
}

close $fp

svm -delete $r

exit
