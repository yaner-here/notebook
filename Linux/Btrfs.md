```shell
$ btrfs filesystem usage /
	Overall:
	    Device size:		 899.01GiB
	    Device allocated:		  27.02GiB
	    Device unallocated:		 871.99GiB
	    Device missing:		     0.00B
	    Device slack:		     0.00B
	    Used:			  22.51GiB
	    Free (estimated):		 874.58GiB	(min: 438.58GiB)
	    Free (statfs, df):		 874.58GiB
	    Data ratio:			      1.00
	    Metadata ratio:		      2.00
	    Global reserve:		  54.05MiB	(used: 0.00B)
	    Multiple profiles:		        no
	
	Data,single: Size:23.01GiB, Used:20.42GiB (88.73%)
	   /dev/sda3	  23.01GiB
	
	Metadata,DUP: Size:2.00GiB, Used:1.05GiB (52.37%)
	   /dev/sda3	   4.00GiB
	
	System,DUP: Size:8.00MiB, Used:16.00KiB (0.20%)
	   /dev/sda3	  16.00MiB
	
	Unallocated:
	   /dev/sda3	 871.99GiB
```

