# Github Dataset

This is a sample usage of attempting to run a search on the linux Github repository dataset.

## Data:

The data will be available online at `something.something.com/data.xml`. Download it to your `data` folder. The naming won't matter, but for this example we will reference the file as `data.xml`.

Here is a snippet of what the file should look like:
```
<data>  <version>
                <page>
                        <title>arch alpha boot bootp c</title>
                        <content>find pa load pal init runkernel start kernel archalphabootbootpc copyright c 1997 jay estabrook this file is used for creating a bootp file for the linuxaxp kernel based significantly on the archalphabootmainc of linus torvalds find a physical address of a virtual object this is easy using the virtual page table address this function moves into osf1 palcode and has a temporary pcb for that the kernel proper should replace this pcb with the real one as soon as possible the page table muckery in here depends on the fact that the boot code has the l1 page table identitymap itself in the second pte in the l1 page table thus the l1page is virtually addressable itself through three levels at virtual address 0x200802000 create the dummy pcb a0 2 osf a1 return address but we give the asm the vaddr of the pcb a2 physical addr of pcb a3 new virtual page table pointer a4 ksp but the asm sets it do it directly in case we are smp start the kernel no outputs it doesnt even return note that this crufty stuff with static and envval and envbuf is because 1 frequently the stack is short and we dont want to overrun 2 frequently the stack is where we are going to copy the kernel to 3 a certain srm console required the get env output to stack a comment in the aboot sources indicates that the get env destination must be quadword aligned might this explain the behaviour rather than requiring output to the stack which seems rather farfetched the initrd must be pagealigned see below for the cause of the magic number 5 move the stack to a safe place to ensure it wont be overwritten by kernel image note no callbacks or printouts from here on out this is a hack as some consoles seem to get virtual 20000000 ie where the srm console puts the kernel bootp image memory overlapping physical memory where the kernel wants to be put which causes real problems when attempting to copy the former to the latter so we first move the kernel virtualtophysical way above where we physically want the kernel to end up then copy it from there to its final resting place sigh</content>
                </page>
                <page>
                        <title>arch alpha boot bootpz c</title>
                        <content>check range find pa pal init runkernel start kernel archalphabootbootpzc copyright c 1997 jay estabrook this file is used for creating a compressed bootp file for the linuxaxp kernel based significantly on the archalphabootmainc of linus torvalds and the decompression code from milo fixme fixme fixme 2mb for now fixme fixme fixme warning note it is very possible that turning on additional messages may cause kernel image corruption due to stack usage to do the printing find a physical address of a virtual object this is easy using the virtual page table address do some range checking for detecting an overlap this function moves into osf1 palcode and has a temporary pcb for that the kernel proper should replace this pcb with the real one as soon as possible the page table muckery in here depends on the fact that the boot code has the l1 page table identitymap itself in the second pte in the l1 page table thus the l1page is virtually addressable itself through three levels at virtual address 0x200802000 create the dummy pcb a0 2 osf a1 return address but we give the asm the vaddr of the pcb a2 physical addr of pcb a3 new virtual page table pointer a4 ksp but the asm sets it do it directly in case we are smp start the kernel no outputs it doesnt even return must record the sp it is virtual on entry so we can make sure not to overwrite it during movement or decompression calculate the kernel image address based on the end of the bootp bootstrapper ie this program round address to next higher page boundary defines from includeasmalphasystemh boot addr virtual address at which the consoles loads the bootp image kernel start kseg address at which the kernel is built to run which includes some initial data pages before the code start addr kseg address of the entry point of kernel code zero pge kseg address of page full of zeroes but upon entry to kerne cvan be expected to hold the parameter list and possible intrd information these are used in the local defines below virtual addresses for the bootp image note that this includes the bootstrapper code as well as the compressed kernel image and possibly the initrd image oh and do not forget the stack which appears to be placed virtually beyond the end of the loaded image virtual addresses for just the bootstrapper part of the bootp image virtual addresses for just the data part of the bootp image this may also include the initrd image but always includes the stack kseg addresses for the uncompressed kernel note that the end address includes workspace for the decompression note also that the data start address is zero pge to which we write just before jumping to the kernel image at start addr define to where we may have to decompress the kernel image before we move it to the final position in case of overlap this will be above the final position of the kernel regardless of overlap we move the initrd image to the end of this copy area because there needs to be a buffer area after the kernel for bootmem anyway reserve one page below initrd for the new stack initialize these for the decompressioninplace situation which is the smallest amount of work and most likely to occur when using the normal start addr of the kernel currently set to 16mb to clear all console code note that this crufty stuff with static and envval and envbuf is because 1 frequently the stack is short and we dont want to overrun 2 frequently the stack is where we are going to copy the kernel to 3 a certain srm console required the get env output to stack a comment in the aboot sources indicates that the get env destination must be quadword aligned might this explain the behaviour rather than requiring output to the stack which seems rather farfetched validity check the hwrpb palcode reinitialization get the parameter list from the console environment variable since all the srm consoles load the bootp image at virtual 0x20000000 we have to ensure that the physical memory pages occupied by that image do not overlap the physical address range where the kernel wants to be run this causes real problems when attempting to cdecompress the former into the latter so we may have to decompressmove the kernelinitrd image virtualtophysical someplace else first before moving kernel initrd to their final resting places sigh first check to see if the range of addresses occupied by the bootstrapper part of the bootp image include any of the physical pages into which the kernel will be placed for execution we only need check on the final kernel image range since we will put the initrd someplace that we can be sure is not in conflict next check to see if the range of addresses occupied by the compressed kernelinitrdstack portion of the bootp image include any of the physical pages into which the decompressed kernel or the initrd will be placed for execution finally check to see if the range of addresses occupied by the compressed kernelinitrd part of the bootp image include any of the physical pages into which that part is to be copied for decompression keep as close as possible to end of bootp image now move things to their final positions ifas required first we always move the initrd image if present initrd image size next we may have to move the uncompressed kernel to the final destination move the stack to a safe place to ensure it wont be overwritten by kernel image clear the zero page then move the argument list in finally set the initrd paramenters for the kernel initrd image size</content>
                </page>
                <page>
```

## Query:
There are two scripts that enable you to run the search: `run_single_query_search.sh` and `run_batch_query_search.sh`.

### Usage with `run_single_query_search.sh`:

Using the single query searcher is the easiest way to run the search. Here is an example query that would be run on the above dataset:
```
./run_single_query_search.sh "start kernel" 5
```
The output of the search can be found in the `target/final_results.txt` file. Here is what the output should look like:
```
Results for: start kernel
vid: 155835     score: 0.263889
vid: 136470     score: 0.263889
vid: 117103     score: 0.263889
vid: 97737      score: 0.263889
vid: 78370      score: 0.263889
vid: 686        score: 0.263889
vid: 20233      score: 0.263889
vid: 39626      score: 0.263889
vid: 59003      score: 0.263889
vid: 175197     score: 0.263889
```

### Usage with `run_batch_query_search.sh`:
Using the batch query searcher requires you to supply a file path which will have new-line separated queries. Here is an example `queries_all.txt` file we used for the linux github repository dataset:
```
virtually addressable
kernel image
```
To run the batch query script type:
```bash
./run_batch_query_search.sh query/queries_all.txt
```

Here is what the `target/final_results.txt` file should look like:
```
Results for: virtual address
vid: 178555     score: 0.194444
vid: 159193     score: 0.194444
vid: 139829     score: 0.194444
vid: 120462     score: 0.194444
vid: 101096     score: 0.194444
vid: 81729      score: 0.194444
vid: 4045       score: 0.194444
vid: 23592      score: 0.194444
vid: 42985      score: 0.194444
vid: 62362      score: 0.194444
Results for: kernel imag
vid: 175383     score: 0.236111
vid: 156021     score: 0.236111
vid: 136656     score: 0.236111
vid: 117289     score: 0.236111
vid: 97923      score: 0.236111
vid: 78556      score: 0.236111
vid: 59189      score: 0.236111
vid: 39812      score: 0.236111
vid: 20419      score: 0.236111
vid: 872        score: 0.236111
```
