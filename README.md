# 内核_进程_Processes  

*20230727*  

## 进程、轻量级进程和线程 Processes,Lightweight Processes,and Threads

A process is an instance of a program in execution;Each of threads represents an execution flow of the process;Linux uses LWP to offer better support for multithreaded applications.

进程是程序执行时的一个实例；每个线程代表进程的一个执行流；轻量级进程是内核对多线程应用提供的支持。

## 进程描述符 Process Descriptor

```
struct task_struct:

  struct thread_info  thread_info | CONFIG_THREAD_INFO_IN_TASK

  unsigned int   __state

  unsigned int   saved_state | CONFIG_PREEMPT_RT

  randomized_struct_fields_start
  
    void    *stack 
    refcount_t   usage 
    unsigned int   flags 
    unsigned int   ptrace
   
    int    on_cpu | CONFIG_SMP
    struct __call_single_node wake_entry | CONFIG_SMP
    unsigned int   wakee_flips | CONFIG_SMP
    unsigned long   wakee_flip_decay_ts | CONFIG_SMP
    struct task_struct  *last_wakee | CONFIG_SMP
    int    recent_used_cpu | CONFIG_SMP
    int    wake_cpu  | CONFIG_SMP
      
    int    on_rq 
   
    int    prio 
    int    static_prio 
    int    normal_prio 
    unsigned int   rt_priority 
   
    struct sched_entity  se 
    struct sched_rt_entity  rt 
    struct sched_dl_entity  dl 
    const struct sched_class *sched_class 
   
    struct rb_node   core_node | CONFIG_SCHED_CORE
    unsigned long   core_cookie | CONFIG_SCHED_CORE
    unsigned int   core_occupation | CONFIG_SCHED_CORE
   
    struct task_group  *sched_task_group | CONFIG_CGROUP_SCHED
   
    struct uclamp_se  uclamp_req[UCLAMP_CNT] | CONFIG_UCLAMP_TASK
    struct uclamp_se  uclamp[UCLAMP_CNT] | CONFIG_UCLAMP_TASK
   
    struct sched_statistics         stats
   
    struct hlist_head  preempt_notifiers | CONFIG_PREEMPT_NOTIFIERS
   
    unsigned int   btrace_seq | CONFIG_BLK_DEV_IO_TRACE
   
    unsigned int   policy 
    int    nr_cpus_allowed 
    const cpumask_t   *cpus_ptr 
    cpumask_t   *user_cpus_ptr 
    cpumask_t   cpus_mask 
    void    *migration_pending 
   
    unsigned short   migration_disabled | CONFIG_SMP
   
    unsigned short   migration_flags 
   
    int    rcu_read_lock_nesting | CONFIG_PREEMPT_RCU
    union rcu_special  rcu_read_unlock_special | CONFIG_PREEMPT_RCU
    struct list_head  rcu_node_entry | CONFIG_PREEMPT_RCU
    struct rcu_node   *rcu_blocked_node | CONFIG_PREEMPT_RCU
   
    unsigned long   rcu_tasks_nvcsw | CONFIG_TASKS_RCU
    u8    rcu_tasks_holdout | CONFIG_TASKS_RCU
    u8    rcu_tasks_idx | CONFIG_TASKS_RCU
    int    rcu_tasks_idle_cpu | CONFIG_TASKS_RCU
    struct list_head  rcu_tasks_holdout_list | CONFIG_TASKS_RCU
   
    int    trc_reader_nesting | CONFIG_TASKS_TRACE_RCU
    int    trc_ipi_to_cpu | CONFIG_TASKS_TRACE_RCU
    union rcu_special  trc_reader_special | CONFIG_TASKS_TRACE_RCU
    struct list_head  trc_holdout_list | CONFIG_TASKS_TRACE_RCU
    struct list_head  trc_blkd_node | CONFIG_TASKS_TRACE_RCU
    int    trc_blkd_cpu | CONFIG_TASKS_TRACE_RCU
    
    struct sched_info  sched_info 
   
    struct list_head  tasks 
   
    struct plist_node  pushable_tasks | CONFIG_SMP
    struct rb_node   pushable_dl_tasks | CONFIG_SMP
   
    struct mm_struct  *mm 
    struct mm_struct  *active_mm 
   
    int    exit_state 
    int    exit_code 
    int    exit_signal 
    int    pdeath_signal 
    unsigned long   jobctl 
   
    unsigned int   personality 
   
    unsigned   sched_reset_on_fork:1 
    unsigned   sched_contributes_to_load:1 
    unsigned   sched_migrated:1 
   
    unsigned   :0 
   
    unsigned   sched_remote_wakeup:1 
   
    unsigned   in_execve:1 
    unsigned   in_iowait:1 
   
    unsigned   restore_sigmask:1 | TIF_RESTORE_SIGMASK
   
    unsigned   in_lru_fault:1 | CONFIG_LRU_GEN
   
    unsigned   brk_randomized:1 | CONFIG_COMPAT_BRK
   
    unsigned   no_cgroup_migration:2 | CONFIG_CGROUPS
   
    unsigned   frozen:1 | CONFIG_CGROUPS
   
    unsigned   use_memdelay:1 | CONFIG_BLK_CGROUP
    
    unsigned   in_memstall:1 | CONFIG_PSI
   
    unsigned   in_page_owner:1 | CONFIG_PAGE_OWNER
   
    unsigned   in_eventfd:1 | CONFIG_EVENTFD
   
    unsigned   pasid_activated:1 | CONFIG_IOMMU_SVA
   
    unsigned   reported_split_lock:1 | CONFIG_CPU_SUP_INTEL
   
    unsigned   in_thrashing:1 | CONFIG_TASK_DELAY_ACCT
   
    unsigned long   atomic_flags  
   
    struct restart_block  restart_block 
   
    pid_t    pid 
    pid_t    tgid 
   
    unsigned long   stack_canary | CONFIG_STACKPROTECTOR
   
    struct task_struct __rcu *real_parent 
   
    struct task_struct __rcu *parent 
   
    struct list_head  children 
    struct list_head  sibling 
    struct task_struct  *group_leader 
   
    struct list_head  ptraced 
    struct list_head  ptrace_entry 
   
    struct pid   *thread_pid 
    struct hlist_node  pid_links[PIDTYPE_MAX] 
    struct list_head  thread_group 
    struct list_head  thread_node 
   
    struct completion  *vfork_done 
   
    int __user   *set_child_tid 
   
    int __user   *clear_child_tid 
   
    void    *worker_private 
   
    u64    utime 
    u64    stime 
   
    u64    utimescaled | CONFIG_ARCH_HAS_SCALED_CPUTIME
    u64    stimescaled | CONFIG_ARCH_HAS_SCALED_CPUTIME
   
    u64    gtime 
    struct prev_cputime  prev_cputime 
   
    struct vtime   vtime | CONFIG_VIRT_CPU_ACCOUNTING_GEN
   
    atomic_t   tick_dep_mask | CONFIG_NO_HZ_FULL
   
    unsigned long   nvcsw 
    unsigned long   nivcsw 
   
    u64    start_time 
   
    u64    start_boottime 
   
    unsigned long   min_flt 
    unsigned long   maj_flt 
   
    struct posix_cputimers  posix_cputimers 
   
    struct posix_cputimers_work posix_cputimers_work | CONFIG_POSIX_CPU_TIMERS_TASK_WORK
   
    const struct cred __rcu  *ptracer_cred 
   
    const struct cred __rcu  *real_cred 
   
    const struct cred __rcu  *cred 
   
    struct key   *cached_requested_key | CONFIG_KEYS 
   
    char    comm[TASK_COMM_LEN] 
   
    struct nameidata  *nameidata 
   
    struct sysv_sem   sysvsem | CONFIG_SYSVIPC
    struct sysv_shm   sysvshm | CONFIG_SYSVIPC
   
    unsigned long   last_switch_count | CONFIG_DETECT_HUNG_TASK
    unsigned long   last_switch_time | CONFIG_DETECT_HUNG_TASK
   
    struct fs_struct  *fs 
   
    struct files_struct  *files 
   
    struct io_uring_task  *io_uring | CONFIG_IO_URING
   
    struct nsproxy   *nsproxy 
   
    struct signal_struct  *signal 
    struct sighand_struct __rcu  *sighand 
    sigset_t   blocked 
    sigset_t   real_blocked 
    
    sigset_t   saved_sigmask 
    struct sigpending  pending 
    unsigned long   sas_ss_sp 
    size_t    sas_ss_size 
    unsigned int   sas_ss_flags 
   
    struct callback_head  *task_works 
   
    struct audit_context  *audit_context | CONFIG_AUDIT && CONFIG_AUDITSYSCALL
    kuid_t    loginuid | CONFIG_AUDIT
    unsigned int   sessionid | CONFIG_AUDIT
   
    struct seccomp   seccomp 
    struct syscall_user_dispatch syscall_dispatch 
   
    u64    parent_exec_id 
    u64    self_exec_id 
   
    spinlock_t   alloc_lock 
   
    raw_spinlock_t   pi_lock 
   
    struct wake_q_node  wake_q 
   
    struct rb_root_cached  pi_waiters | CONFIG_RT_MUTEXES
    struct task_struct  *pi_top_task | CONFIG_RT_MUTEXES
    struct rt_mutex_waiter  *pi_blocked_on | CONFIG_RT_MUTEXES
   
    struct mutex_waiter  *blocked_on | CONFIG_DEBUG_MUTEXES 
   
    int    non_block_count | CONFIG_DEBUG_ATOMIC_SLEEP 
   
    struct irqtrace_events  irqtrace | CONFIG_TRACE_IRQFLAGS
    unsigned int   hardirq_threaded | CONFIG_TRACE_IRQFLAGS
    u64    hardirq_chain_key | CONFIG_TRACE_IRQFLAGS
    int    softirqs_enabled | CONFIG_TRACE_IRQFLAGS
    int    softirq_context | CONFIG_TRACE_IRQFLAGS
    int    irq_config | CONFIG_TRACE_IRQFLAGS
   
    int    softirq_disable_cnt | CONFIG_PREEMPT_RT 
   
    # define MAX_LOCK_DEPTH   48UL | CONFIG_LOCKDEP
    u64    curr_chain_key  | CONFIG_LOCKDEP
    int    lockdep_depth  | CONFIG_LOCKDEP
    unsigned int   lockdep_recursion  | CONFIG_LOCKDEP
    struct held_lock  held_locks[MAX_LOCK_DEPTH]  | CONFIG_LOCKDEP
   
    unsigned int   in_ubsan | CONFIG_UBSAN && ! CONFIG_UBSAN_TRAP
   
    void    *journal_info 
   
    struct bio_list   *bio_list 
   
    struct blk_plug   *plug 
   
    struct reclaim_state  *reclaim_state 
   
    struct io_context  *io_context
   
    struct capture_control  *capture_control | CONFIG_COMPACTION
   
    unsigned long   ptrace_message 
    kernel_siginfo_t  *last_siginfo 
   
    struct task_io_accounting ioac 
   
    unsigned int   psi_flags | CONFIG_PSI
   
    u64    acct_rss_mem2 | CONFIG_TASK_XACCT
    u64    acct_vm_mem1 | CONFIG_TASK_XACCT
    u64    acct_timexpd  | CONFIG_TASK_XACCT
   
    nodemask_t   mems_allowed | CONFIG_CPUSETS
    seqcount_spinlock_t  mems_allowed_seq | CONFIG_CPUSETS
    int    cpuset_mem_spread_rotor | CONFIG_CPUSETS
    int    cpuset_slab_spread_rotor| CONFIG_CPUSETS
   
    struct css_set __rcu  *cgroups | CONFIG_CGROUPS
    struct list_head  cg_list| CONFIG_CGROUPS
   
    u32    closid | CONFIG_X86_CPU_RESCTRL
    u32    rmid | CONFIG_X86_CPU_RESCTRL
   
    struct robust_list_head __user *robust_list | CONFIG_FUTEX
    struct compat_robust_list_head __user *compat_robust_list | CONFIG_FUTEX && CONFIG_COMPAT
    struct list_head  pi_state_list | CONFIG_FUTEX
    struct futex_pi_state  *pi_state_cache | CONFIG_FUTEX
    struct mutex   futex_exit_mutex | CONFIG_FUTEX
    unsigned int   futex_state | CONFIG_FUTEX
   
    struct perf_event_context *perf_event_ctxp | CONFIG_PERF_EVENTS
    struct mutex   perf_event_mutex | CONFIG_PERF_EVENTS
    struct list_head  perf_event_list| CONFIG_PERF_EVENTS
   
    unsigned long   preempt_disable_ip | CONFIG_DEBUG_PREEMPT
   
    struct mempolicy  *mempolicy | CONFIG_NUMA
    short    il_prev | CONFIG_NUMA
    short    pref_node_fork| CONFIG_NUMA
   
    int    numa_scan_seq | CONFIG_NUMA_BALANCING
    unsigned int   numa_scan_period | CONFIG_NUMA_BALANCING
    unsigned int   numa_scan_period_max | CONFIG_NUMA_BALANCING
    int    numa_preferred_nid | CONFIG_NUMA_BALANCING
    unsigned long   numa_migrate_retry | CONFIG_NUMA_BALANCING
   
    u64    node_stamp | CONFIG_NUMA_BALANCING
    u64    last_task_numa_placement | CONFIG_NUMA_BALANCING
    u64    last_sum_exec_runtime | CONFIG_NUMA_BALANCING
    struct callback_head  numa_work | CONFIG_NUMA_BALANCING
   
    struct numa_group __rcu  *numa_group | CONFIG_NUMA_BALANCING
   
    unsigned long   *numa_faults | CONFIG_NUMA_BALANCING
    unsigned long   total_numa_faults | CONFIG_NUMA_BALANCING
   
    unsigned long   numa_faults_locality[3] | CONFIG_NUMA_BALANCING
   
    unsigned long   numa_pages_migrated | CONFIG_NUMA_BALANCING
   
    struct rseq __user *rseq | CONFIG_RSEQ
    u32 rseq_len | CONFIG_RSEQ
    u32 rseq_sig | CONFIG_RSEQ
   
    int    mm_cid  | CONFIG_SCHED_MM_CID
    int    last_mm_cid  | CONFIG_SCHED_MM_CID
    int    migrate_from_cpu | CONFIG_SCHED_MM_CID
    int    mm_cid_active  | CONFIG_SCHED_MM_CID
    struct callback_head  cid_work | CONFIG_SCHED_MM_CID
   
    struct tlbflush_unmap_batch tlb_ubc 
   
    struct pipe_inode_info  *splice_pipe 
   
    struct page_frag  task_frag
   
    struct task_delay_info  *delays | CONFIG_TASK_DELAY_ACCT
   
    int    make_it_fail | CONFIG_FAULT_INJECTION
    unsigned int   fail_nth | CONFIG_FAULT_INJECTION
   
    int    nr_dirtied 
    int    nr_dirtied_pause 
   
    unsigned long   dirty_paused_when 
   
    int    latency_record_count  | CONFIG_LATENCYTOP                      
    struct latency_record  latency_record[LT_SAVECOUNT] | CONFIG_LATENCYTOP
   
    u64    timer_slack_ns 
    u64    default_timer_slack_ns 
   
    unsigned int   kasan_depth | CONFIG_KASAN_GENERIC || CONFIG_KASAN_SW_TAGS
   
    struct kcsan_ctx  kcsan_ctx | CONFIG_KCSAN
    struct irqtrace_events  kcsan_save_irqtrace | CONFIG_KCSAN && CONFIG_TRACE_IRQFLAGS
    int    kcsan_stack_depth | CONFIG_KCSAN && CONFIG_KCSAN_WEAK_MEMORY
   
    struct kmsan_ctx  kmsan_ctx | CONFIG_KMSAN
   
    struct kunit   *kunit_test | IS_ENABLED(CONFIG_KUNIT)
   
    int    curr_ret_stack | CONFIG_FUNCTION_GRAPH_TRACER 
    int    curr_ret_depth | CONFIG_FUNCTION_GRAPH_TRACER
   
    struct ftrace_ret_stack  *ret_stack | CONFIG_FUNCTION_GRAPH_TRACER
   
    unsigned long long  ftrace_timestamp | CONFIG_FUNCTION_GRAPH_TRACER
   
    atomic_t   trace_overrun | CONFIG_FUNCTION_GRAPH_TRACER
   
    atomic_t   tracing_graph_pause | CONFIG_FUNCTION_GRAPH_TRACER
   
    unsigned long   trace_recursion | CONFIG_TRACING 
   
    unsigned int   kcov_mode | CONFIG_KCOV 
   
    unsigned int   kcov_size | CONFIG_KCOV 
   
    void    *kcov_area | CONFIG_KCOV
   
    struct kcov   *kcov | CONFIG_KCOV
   
    u64    kcov_handle | CONFIG_KCOV
   
    int    kcov_sequence | CONFIG_KCOV
   
    unsigned int   kcov_softirq | CONFIG_KCOV
   
    struct mem_cgroup  *memcg_in_oom | CONFIG_MEMCG
    gfp_t    memcg_oom_gfp_mask | CONFIG_MEMCG
    int    memcg_oom_order | CONFIG_MEMCG
   
    unsigned int   memcg_nr_pages_over_high | CONFIG_MEMCG 
   
    struct mem_cgroup  *active_memcg | CONFIG_MEMCG
   
    struct gendisk   *throttle_disk | CONFIG_BLK_CGROUP 
   
    struct uprobe_task  *utask | CONFIG_UPROBES
   
    unsigned int   sequential_io | CONFIG_BCACHE || CONFIG_BCACHE_MODULE
    unsigned int   sequential_io_avg | CONFIG_BCACHE || CONFIG_BCACHE_MODULE
   
    struct kmap_ctrl  kmap_ctrl 
   
    unsigned long   task_state_change | CONFIG_DEBUG_ATOMIC_SLEEP
    unsigned long   saved_state_change | CONFIG_DEBUG_ATOMIC_SLEEP && CONFIG_PREEMPT_RT
   
    struct rcu_head   rcu 
    refcount_t   rcu_users 
    int    pagefault_disabled 
   
    struct task_struct  *oom_reaper_list  | CONFIG_MMU
    struct timer_list  oom_reaper_timer | CONFIG_MMU
   
    struct vm_struct  *stack_vm_area | CONFIG_VMAP_STACK 
   
    refcount_t   stack_refcount | CONFIG_THREAD_INFO_IN_TASK 
   
    int patch_state | CONFIG_LIVEPATCH 
   
    void    *security | CONFIG_SECURITY 
   
    struct bpf_local_storage __rcu *bpf_storage | CONFIG_BPF_SYSCALL
   
    struct bpf_run_ctx  *bpf_ctx | CONFIG_BPF_SYSCALL
   
    unsigned long   lowest_stack | CONFIG_GCC_PLUGIN_STACKLEAK
    unsigned long   prev_lowest_stack | CONFIG_GCC_PLUGIN_STACKLEAK
   
    void __user   *mce_vaddr | CONFIG_X86_MCE
    __u64    mce_kflags | CONFIG_X86_MCE
    
    u64    mce_addr  | CONFIG_X86_MCE
    __u64    mce_ripv : 1, mce_whole_page : 1, __mce_reserved : 62  | CONFIG_X86_MCE
    struct callback_head  mce_kill_me  | CONFIG_X86_MCE
    int    mce_count  | CONFIG_X86_MCE
   
    struct llist_head               kretprobe_instances | CONFIG_KRETPROBES
   
    struct llist_head               rethooks | CONFIG_RETHOOK
   
    struct callback_head  l1d_flush_kill  | CONFIG_ARCH_HAS_PARANOID_L1D_FLUSH
   
    union rv_task_monitor  rv[RV_PER_TASK_MONITORS] | CONFIG_RV
   
    struct user_event_mm  *user_event_mm  | CONFIG_USER_EVENTS

  randomized_struct_fields_end
 
  struct thread_struct  thread 
  
```

* CONFIG_THREAD_INFO_IN_TASK

```
config THREAD_INFO_IN_TASK
	bool
	help
	  Select this to move thread_info off the stack into task_struct.  To
	  make this work, an arch will need to remove all thread_info fields
	  except flags and fix any runtime bugs.

	  One subtle change that will be needed is to use try_get_task_stack()
	  and put_task_stack() in save_thread_stack_tsk() and get_wchan().
```

选择此选项可将thread_info从堆栈移到task_struct中。要做到这一点，arch需要删除除flags以外的所有thread_info字段，并修复任何运行时错误。

需要做的一个细微的改变是在save_thread_stack_tsk()和get_wchan()中使用try_get_task_stack()和put_task_stack()。

* CONFIG_PREEMPT_RT

```
config PREEMPT_RT
	bool "Fully Preemptible Kernel (Real-Time)"
	depends on EXPERT && ARCH_SUPPORTS_RT
	select PREEMPTION
	help
	  This option turns the kernel into a real-time kernel by replacing
	  various locking primitives (spinlocks, rwlocks, etc.) with
	  preemptible priority-inheritance aware variants, enforcing
	  interrupt threading and introducing mechanisms to break up long
	  non-preemptible sections. This makes the kernel, except for very
	  low level and critical code paths (entry code, scheduler, low
	  level interrupt handling) fully preemptible and brings most
	  execution contexts under scheduler control.

	  Select this if you are building a kernel for systems which
	  require real-time guarantees.
```

这个选项通过用可抢占的优先级继承感知变量替换各种锁原语(自旋锁、rwlocks等)、强制中断线程和引入分解长不可抢占部分的机制，将内核变成了实时内核。这使得内核(除了非常低级和关键的代码路径(入口代码、调度器、低级中断处理)完全可抢占，并将大多数执行上下文置于调度器控制之下。

如果您正在为需要实时保证的系统构建内核，请选择此选项。

* CONFIG_SMP

```
config SMP
	bool "Symmetric Multi-Processing (SMP) support for C-SKY"
	depends on CPU_CK860
	default n
```

* CONFIG_SCHED_CORE

```
config SCHED_CORE
	bool "Core Scheduling for SMT"
	depends on SCHED_SMT
	help
	  This option permits Core Scheduling, a means of coordinated task
	  selection across SMT siblings. When enabled -- see
	  prctl(PR_SCHED_CORE) -- task selection ensures that all SMT siblings
	  will execute a task from the same 'core group', forcing idle when no
	  matching task is found.

	  Use of this feature includes:
	   - mitigation of some (not all) SMT side channels;
	   - limiting SMT interference to improve determinism performance.

	  SCHED_CORE is default disabled. When it is enabled and unused,
	  which is the likely usage by Linux distributions, there should
	  be no measurable impact on performance.
```

该选项支持核心调度，这是跨SMT兄弟节点协调任务选择的一种方法。启用后 -- 请参阅prctl(PR_SCHED_CORE) -- 任务选择确保所有SMT兄弟节点都将执行来自同一“核心组”的任务，在没有找到匹配的任务时强制空闲。

此功能的使用包括:
* 缓解一些(不是全部)SMT侧信道
* 限制SMT干扰以提高与或性能。

SCHED_CORE默认是禁用的。当它被启用和未使用时(这是Linux发行版可能使用的情况)，应该不会对性能产生可测量的影响。

* CONFIG_CGROUP_SCHED

```
menuconfig CGROUP_SCHED
	bool "CPU controller"
	default n
	help
	  This feature lets CPU scheduler recognize task groups and control CPU
	  bandwidth allocation to such task groups. It uses cgroups to group
	  tasks.
```

这个特性允许CPU调度器识别任务组并控制分配给这些任务组的CPU带宽。它使用cgroups对任务进行分组。

* CONFIG_UCLAMP_TASK

```
config UCLAMP_TASK
	bool "Enable utilization clamping for RT/FAIR tasks"
	depends on CPU_FREQ_GOV_SCHEDUTIL
	help
	  This feature enables the scheduler to track the clamped utilization
	  of each CPU based on RUNNABLE tasks scheduled on that CPU.

	  With this option, the user can specify the min and max CPU
	  utilization allowed for RUNNABLE tasks. The max utilization defines
	  the maximum frequency a task should use while the min utilization
	  defines the minimum frequency it should use.

	  Both min and max utilization clamp values are hints to the scheduler,
	  aiming at improving its frequency selection policy, but they do not
	  enforce or grant any specific bandwidth for tasks.

	  If in doubt, say N.
```

这个特性使调度器能够根据调度在每个CPU上的RUNNABLE任务跟踪每个CPU的固定利用率。

有了这个选项，用户可以指定允许RUNNABLE任务使用的最小和最大CPU利用率。最大利用率定义了任务应该使用的最大频率，而最小利用率定义了任务应该使用的最小频率。

最小和最大利用率箝位值都是对调度器的提示，旨在改进其频率选择策略，但它们不会为任务强制或授予任何特定带宽。

* CONFIG_PREEMPT_NOTIFIERS

```
config PREEMPT_NOTIFIERS
	bool
```

* CONFIG_BLK_DEV_IO_TRACE

```
config BLK_DEV_IO_TRACE
	bool "Support for tracing block IO actions"
	depends on SYSFS
	depends on BLOCK
	select RELAY
	select DEBUG_FS
	select TRACEPOINTS
	select GENERIC_TRACER
	select STACKTRACE
	help
	  Say Y here if you want to be able to trace the block layer actions
	  on a given queue. Tracing allows you to see any traffic happening
	  on a block device queue. For more information (and the userspace
	  support tools needed), fetch the blktrace tools from:

	  git://git.kernel.dk/blktrace.git

	  Tracing also is possible using the ftrace interface, e.g.:

	    echo 1 > /sys/block/sda/sda1/trace/enable
	    echo blk > /sys/kernel/tracing/current_tracer
	    cat /sys/kernel/tracing/trace_pipe

	  If unsure, say N.
```

如果您希望能够跟踪给定队列上的块层动作，则在这里输入Y。跟踪允许您查看在块设备队列上发生的任何流量。

* CONFIG_PREEMPT_RCU

```
config PREEMPT_RCU
	bool
	default y if PREEMPTION
	select TREE_RCU
	help
	  This option selects the RCU implementation that is
	  designed for very large SMP systems with hundreds or
	  thousands of CPUs, but for which real-time response
	  is also required.  It also scales down nicely to
	  smaller systems.

	  Select this option if you are unsure.
```

该选项选择的RCU实现是为拥有数百或数千个cpu的大型SMP系统设计的，但也需要实时响应。它也可以很好地缩小到更小的系统。

* CONFIG_TASKS_RCU

```
config TASKS_RCU
	bool
	default n
	select IRQ_WORK
```

* CONFIG_TASKS_TRACE_RCU

```
config TASKS_TRACE_RCU
	bool
	default n
	select IRQ_WORK
```

* TIF_RESTORE_SIGMASK

```

```

* CONFIG_LRU_GEN

```
config LRU_GEN
	bool "Multi-Gen LRU"
	depends on MMU
	# make sure folio->flags has enough spare bits
	depends on 64BIT || !SPARSEMEM || SPARSEMEM_VMEMMAP
	help
	  A high performance LRU implementation to overcommit memory. See
	  Documentation/admin-guide/mm/multigen_lru.rst for details.
```

* CONFIG_COMPAT_BRK

```
config COMPAT_BRK
	bool "Disable heap randomization"
	default y
	help
	  Randomizing heap placement makes heap exploits harder, but it
	  also breaks ancient binaries (including anything libc5 based).
	  This option changes the bootup default to heap randomization
	  disabled, and can be overridden at runtime by setting
	  /proc/sys/kernel/randomize_va_space to 2.

	  On non-ancient distros (post-2000 ones) N is usually a safe choice.
```

随机化堆放置使得利用堆变得更加困难，但它也会破坏旧的二进制文件(包括任何基于libc5的二进制文件)。

该选项将启动默认设置更改为禁用堆随机化，并且可以在运行时通过将/proc/sys/kernel/randomize_va_space设置为2来覆盖。

* CONFIG_CGROUPS

```
menuconfig CGROUPS
	bool "Control Group support"
	select KERNFS
	help
	  This option adds support for grouping sets of processes together, for
	  use with process control subsystems such as Cpusets, CFS, memory
	  controls or device isolation.
	  See
		- Documentation/scheduler/sched-design-CFS.rst	(CFS)
		- Documentation/admin-guide/cgroup-v1/ (features for grouping, isolation
					  and resource control)

	  Say N if unsure.
```

该选项增加了对进程集分组的支持，以便与进程控制子系统(如Cpusets、CFS、内存控制或设备隔离)一起使用。

* CONFIG_BLK_CGROUP

```
config BLK_CGROUP
	bool "IO controller"
	depends on BLOCK
	default n
	help
	Generic block IO controller cgroup interface. This is the common
	cgroup interface which should be used by various IO controlling
	policies.

	Currently, CFQ IO scheduler uses it to recognize task groups and
	control disk bandwidth allocation (proportional time slice allocation)
	to such task groups. It is also used by bio throttling logic in
	block layer to implement upper limit in IO rates on a device.

	This option only enables generic Block IO controller infrastructure.
	One needs to also enable actual IO controlling logic/policy. For
	enabling proportional weight division of disk bandwidth in CFQ, set
	CONFIG_BFQ_GROUP_IOSCHED=y; for enabling throttling policy, set
	CONFIG_BLK_DEV_THROTTLING=y.

	See Documentation/admin-guide/cgroup-v1/blkio-controller.rst for more information.
```

通用块IO控制器组接口。这是通用的c组接口，应该被各种IO控制策略使用。

目前，CFQ IO调度器使用它来识别任务组，并控制磁盘带宽分配(按比例分配时间片)给这些任务组。它也被用于块层的生物节流逻辑来实现设备上IO速率的上限。

此选项仅启用通用块IO控制器基础结构。还需要启用实际的IO控制逻辑/策略。配置CONFIG_BFQ_GROUP_IOSCHED=y;设置“CONFIG_BLK DEV_THROTTLING=y”，开启节流策略。

* CONFIG_PSI

```
config PSI
	bool "Pressure stall information tracking"
	help
	  Collect metrics that indicate how overcommitted the CPU, memory,
	  and IO capacity are in the system.

	  If you say Y here, the kernel will create /proc/pressure/ with the
	  pressure statistics files cpu, memory, and io. These will indicate
	  the share of walltime in which some or all tasks in the system are
	  delayed due to contention of the respective resource.

	  In kernels with cgroup support, cgroups (cgroup2 only) will
	  have cpu.pressure, memory.pressure, and io.pressure files,
	  which aggregate pressure stalls for the grouped tasks only.

	  For more details see Documentation/accounting/psi.rst.

	  Say N if unsure.
```

收集指示系统中CPU、内存和IO容量过度使用情况的指标。

如果在这里输入Y，内核将创建/proc/pressure/，其中包含压力统计文件cpu、内存和io。这将指示由于各自资源的争用而导致系统中部分或全部任务延迟的运行时间份额。

在支持cgroup的内核中，cgroups(仅cgroup2)将拥有cpu。压力,记忆。压强和io。压力文件，仅为分组任务聚合压力档。

* CONFIG_PAGE_OWNER

```
config PAGE_OWNER
	bool "Track page owner"
	depends on DEBUG_KERNEL && STACKTRACE_SUPPORT
	select DEBUG_FS
	select STACKTRACE
	select STACKDEPOT
	select PAGE_EXTENSION
	help
	  This keeps track of what call chain is the owner of a page, may
	  help to find bare alloc_page(s) leaks. Even if you include this
	  feature on your build, it is disabled in default. You should pass
	  "page_owner=on" to boot parameter in order to enable it. Eats
	  a fair amount of memory if enabled. See tools/mm/page_owner_sort.c
	  for user-space helper.

	  If unsure, say N.
```

这可以跟踪哪个调用链是页面的所有者，可能有助于找到裸alloc_page(s)泄漏。即使在构建中包含此功能，默认情况下它也是禁用的。您应该将“page_owner=on”传递给启动参数以启用它。

* CONFIG_EVENTFD

```
config EVENTFD
	bool "Enable eventfd() system call" if EXPERT
	default y
	help
	  Enable the eventfd() system call that allows to receive both
	  kernel notification (ie. KAIO) or userspace notifications.

	  If unsure, say Y.
```

启用eventfd()系统调用，允许接收内核通知(即.KAIO)或用户空间通知。

* CONFIG_IOMMU_SVA

```
# Shared Virtual Addressing
config IOMMU_SVA
	bool
```

共享虚拟寻址。

* CONFIG_CPU_SUP_INTEL

```
config CPU_SUP_INTEL
	default y
	bool "Support Intel processors" if PROCESSOR_SELECT
	help
	  This enables detection, tunings and quirks for Intel processors

	  You need this enabled if you want your kernel to run on an
	  Intel CPU. Disabling this option on other types of CPUs
	  makes the kernel a tiny bit smaller. Disabling it on an Intel
	  CPU might render the kernel unbootable.

	  If unsure, say N.
```

这使得英特尔处理器的检测、调优和怪癖成为可能。

如果您希望内核在Intel CPU上运行，则需要启用此功能。在其他类型的cpu上禁用此选项使内核变小一点。在Intel CPU上禁用它可能会导致内核无法启动。

* CONFIG_TASK_DELAY_ACCT

```
config TASK_DELAY_ACCT
	bool "Enable per-task delay accounting"
	depends on TASKSTATS
	select SCHED_INFO
	help
	  Collect information on time spent by a task waiting for system
	  resources like cpu, synchronous block I/O completion and swapping
	  in pages. Such statistics can help in setting a task's priorities
	  relative to other tasks for cpu, io, rss limits etc.

	  Say N if unsure.
```

收集任务等待系统资源(如cpu、同步块I/O完成和页面交换)所花费的时间信息。这样的统计数据可以帮助设置任务相对于其他任务的优先级，如cpu、io、rss限制等。

* CONFIG_STACKPROTECTOR

```
config STACKPROTECTOR
	bool "Stack Protector buffer overflow detection"
	depends on HAVE_STACKPROTECTOR
	depends on $(cc-option,-fstack-protector)
	default y
	help
	  This option turns on the "stack-protector" GCC feature. This
	  feature puts, at the beginning of functions, a canary value on
	  the stack just before the return address, and validates
	  the value just before actually returning.  Stack based buffer
	  overflows (that need to overwrite this return address) now also
	  overwrite the canary, which gets detected and the attack is then
	  neutralized via a kernel panic.

	  Functions will have the stack-protector canary logic added if they
	  have an 8-byte or larger character array on the stack.

	  This feature requires gcc version 4.2 or above, or a distribution
	  gcc with the feature backported ("-fstack-protector").

	  On an x86 "defconfig" build, this feature adds canary checks to
	  about 3% of all kernel functions, which increases kernel code size
	  by about 0.3%.
```

这个选项打开“堆栈保护”GCC特性。该特性在函数开始时，在返回地址之前的堆栈上放置一个canary值，并在实际返回之前验证该值。基于堆栈的缓冲区溢出(需要覆盖此返回地址)现在也覆盖了canary，它被检测到，然后通过内核panic消除攻击。

如果函数在堆栈上有8字节或更大的字符数组，则会添加堆栈保护canary逻辑。

此功能需要gcc版本4.2或更高版本，或者带有此功能后移植("- stack-protector")的发行版gcc。

在x86“defconfig”构建中，该特性将canary检查添加到大约3%的内核函数中，从而使内核代码大小增加了大约0.3%。

* CONFIG_ARCH_HAS_SCALED_CPUTIME

```
config ARCH_HAS_SCALED_CPUTIME
	bool
```

* CONFIG_VIRT_CPU_ACCOUNTING_GEN

```
config VIRT_CPU_ACCOUNTING_GEN
	bool "Full dynticks CPU time accounting"
	depends on HAVE_CONTEXT_TRACKING_USER
	depends on HAVE_VIRT_CPU_ACCOUNTING_GEN
	depends on GENERIC_CLOCKEVENTS
	select VIRT_CPU_ACCOUNTING
	select CONTEXT_TRACKING_USER
	help
	  Select this option to enable task and CPU time accounting on full
	  dynticks systems. This accounting is implemented by watching every
	  kernel-user boundaries using the context tracking subsystem.
	  The accounting is thus performed at the expense of some significant
	  overhead.

	  For now this is only useful if you are working on the full
	  dynticks subsystem development.

	  If unsure, say N.
```

选择此选项可在全动态系统上启用任务和CPU时间记帐。这种记帐是通过使用上下文跟踪子系统监视每个内核用户边界来实现的。因此，会计核算是以牺牲一些重要的管理费用为代价的。

目前，这只在从事完整的动态子系统开发时才有用。

* CONFIG_NO_HZ_FULL

```
config NO_HZ_FULL
	bool "Full dynticks system (tickless)"
	# NO_HZ_COMMON dependency
	# We need at least one periodic CPU for timekeeping
	depends on SMP
	depends on HAVE_CONTEXT_TRACKING_USER
	# VIRT_CPU_ACCOUNTING_GEN dependency
	depends on HAVE_VIRT_CPU_ACCOUNTING_GEN
	select NO_HZ_COMMON
	select RCU_NOCB_CPU
	select VIRT_CPU_ACCOUNTING_GEN
	select IRQ_WORK
	select CPU_ISOLATION
	help
	 Adaptively try to shutdown the tick whenever possible, even when
	 the CPU is running tasks. Typically this requires running a single
	 task on the CPU. Chances for running tickless are maximized when
	 the task mostly runs in userspace and has few kernel activity.

	 You need to fill up the nohz_full boot parameter with the
	 desired range of dynticks CPUs to use it. This is implemented at
	 the expense of some overhead in user <-> kernel transitions:
	 syscalls, exceptions and interrupts.

	 By default, without passing the nohz_full parameter, this behaves just
	 like NO_HZ_IDLE.

	 If you're a distro say Y.
```

尽可能自适应地关闭tick，即使CPU正在运行任务。这通常需要在CPU上运行单个任务。当任务主要在用户空间中运行并且内核活动很少时，无问题运行的机会最大。

您需要用所需的动态cpu范围填充nohz_full boot参数来使用它。这是以用户<->内核转换中的一些开销为代价实现的:系统调用、异常和中断。

* CONFIG_POSIX_CPU_TIMERS_TASK_WORK

```
# Select to handle posix CPU timers from task_work
# and not from the timer interrupt context
config HAVE_POSIX_CPU_TIMERS_TASK_WORK
	bool

config POSIX_CPU_TIMERS_TASK_WORK
	bool
	default y if POSIX_TIMERS && HAVE_POSIX_CPU_TIMERS_TASK_WORK
```

选择从task_work处理posix CPU定时器，而不是从定时器中断上下文处理

* CONFIG_KEYS

```
config KEYS
	bool "Enable access key retention support"
	select ASSOCIATIVE_ARRAY
	help
	  This option provides support for retaining authentication tokens and
	  access keys in the kernel.

	  It also includes provision of methods by which such keys might be
	  associated with a process so that network filesystems, encryption
	  support and the like can find them.

	  Furthermore, a special type of key is available that acts as keyring:
	  a searchable sequence of keys. Each process is equipped with access
	  to five standard keyrings: UID-specific, GID-specific, session,
	  process and thread.

	  If you are unsure as to whether this is required, answer N.
```

该选项支持在内核中保留身份验证令牌和访问密钥。

它还提供了一些方法，通过这些方法可以将这些密钥与进程相关联，以便网络文件系统、加密支持等可以找到它们。

此外，有一种特殊类型的密钥可用来充当密匙环:一个可搜索的密钥序列。每个进程都配备了对五个标准密匙环的访问权限:特定于uid、特定于gid、会话、进程和线程。

* CONFIG_SYSVIPC

```
config SYSVIPC
	bool "System V IPC"
	help
	  Inter Process Communication is a suite of library functions and
	  system calls which let processes (running programs) synchronize and
	  exchange information. It is generally considered to be a good thing,
	  and some programs won't run unless you say Y here. In particular, if
	  you want to run the DOS emulator dosemu under Linux (read the
	  DOSEMU-HOWTO, available from <http://www.tldp.org/docs.html#howto>),
	  you'll need to say Y here.

	  You can find documentation about IPC with "info ipc" and also in
	  section 6.4 of the Linux Programmer's Guide, available from
	  <http://www.tldp.org/guides.html>.
```

进程间通信是一套库函数和系统调用，它让进程(运行的程序)同步和交换信息。它通常被认为是一件好事，除非您在这里输入Y，否则一些程序将无法运行。

* CONFIG_DETECT_HUNG_TASK

```
config DETECT_HUNG_TASK
	bool "Detect Hung Tasks"
	depends on DEBUG_KERNEL
	default SOFTLOCKUP_DETECTOR
	help
	  Say Y here to enable the kernel to detect "hung tasks",
	  which are bugs that cause the task to be stuck in
	  uninterruptible "D" state indefinitely.

	  When a hung task is detected, the kernel will print the
	  current stack trace (which you should report), but the
	  task will stay in uninterruptible state. If lockdep is
	  enabled then all held locks will also be reported. This
	  feature has negligible overhead.
```

当检测到挂起的任务时，内核将打印当前堆栈跟踪(您应该报告)，但任务将保持不可中断状态。如果启用了lockdep，那么还将报告所有持有的锁。此功能的开销可以忽略不计。

* CONFIG_IO_URING

```
config IO_URING
	bool "Enable IO uring support" if EXPERT
	select IO_WQ
	default y
	help
	  This option enables support for the io_uring interface, enabling
	  applications to submit and complete IO through submission and
	  completion rings that are shared between the kernel and application.
```

该选项支持io_uring接口，使应用程序能够通过内核和应用程序之间共享的提交和完成环提交和完成IO。

* CONFIG_AUDIT

```
config AUDIT
	bool "Auditing support"
	depends on NET
	help
	  Enable auditing infrastructure that can be used with another
	  kernel subsystem, such as SELinux (which requires this for
	  logging of avc messages output).  System call auditing is included
	  on architectures which support it.
```

启用可以与另一个内核子系统一起使用的审计基础设施，比如SELinux(它需要这个来记录avc消息输出)。系统调用审计包含在支持它的体系结构中。

* CONFIG_RT_MUTEXES

```
config RT_MUTEXES
	bool
	default y if PREEMPT_RT
```

* CONFIG_DEBUG_MUTEXES

```
config DEBUG_MUTEXES
	bool "Mutex debugging: basic checks"
	depends on DEBUG_KERNEL && !PREEMPT_RT
	help
	 This feature allows mutex semantics violations to be detected and
	 reported.
```

该特性允许检测和报告互斥锁语义违反。

* CONFIG_DEBUG_ATOMIC_SLEEP

```
config DEBUG_ATOMIC_SLEEP
	bool "Sleep inside atomic section checking"
	select PREEMPT_COUNT
	depends on DEBUG_KERNEL
	depends on !ARCH_NO_PREEMPT
	help
	  If you say Y here, various routines which may sleep will become very
	  noisy if they are called inside atomic sections: when a spinlock is
	  held, inside an rcu read side critical section, inside preempt disabled
	  sections, inside an interrupt, etc...
```

如果你在这里说Y，各种可能休眠的例程将变得非常嘈杂，如果它们在原子段内被调用:当一个自旋锁被持有时，在一个rcu读侧临界区内，在抢占禁用段内，在中断中，等等…

* CONFIG_TRACE_IRQFLAGS

```
config TRACE_IRQFLAGS
	depends on TRACE_IRQFLAGS_SUPPORT
	bool
	help
	  Enables hooks to interrupt enabling and disabling for
	  either tracing or lock debugging.
```

使钩子能够中断跟踪或锁调试的启用和禁用。

* CONFIG_LOCKDEP

```
config LOCKDEP
	bool
	depends on DEBUG_KERNEL && LOCK_DEBUGGING_SUPPORT
	select STACKTRACE
	select KALLSYMS
	select KALLSYMS_ALL
```

* CONFIG_UBSAN

```
menuconfig UBSAN
	bool "Undefined behaviour sanity checker"
	help
	  This option enables the Undefined Behaviour sanity checker.
	  Compile-time instrumentation is used to detect various undefined
	  behaviours at runtime. For more details, see:
	  Documentation/dev-tools/ubsan.rst
```

此选项启用未定义行为完整性检查器。编译时插装用于在运行时检测各种未定义行为。

* CONFIG_COMPACTION

```
# support for memory compaction
config COMPACTION
	bool "Allow for memory compaction"
	def_bool y
	select MIGRATION
	depends on MMU
	help
	  Compaction is the only memory management component to form
	  high order (larger physically contiguous) memory blocks
	  reliably. The page allocator relies on compaction heavily and
	  the lack of the feature can lead to unexpected OOM killer
	  invocations for high order memory requests. You shouldn't
	  disable this option unless there really is a strong reason for
	  it and then we would be really interested to hear about that at
	  linux-mm@kvack.org.
```

压缩是唯一能够可靠地形成高阶(较大的物理连续)内存块的内存管理组件。页面分配器严重依赖于压缩，缺少该特性可能会导致对高阶内存请求的意外的OOM杀手级调用。

* CONFIG_TASK_XACCT

```
config TASK_XACCT
	bool "Enable extended accounting over taskstats"
	depends on TASKSTATS
	help
	  Collect extended task accounting data and send the data
	  to userland for processing over the taskstats interface.

	  Say N if unsure.
```

收集扩展任务记帐数据，并将数据发送到userland，以便通过taskstats接口进行处理。

* CONFIG_CPUSETS

```
config CPUSETS
	bool "Cpuset controller"
	depends on SMP
	help
	  This option will let you create and manage CPUSETs which
	  allow dynamically partitioning a system into sets of CPUs and
	  Memory Nodes and assigning tasks to run only within those sets.
	  This is primarily useful on large SMP or NUMA systems.

	  Say N if unsure.
```

该选项允许您创建和管理cpuset，它允许动态地将系统划分为cpu和内存节点集，并分配只在这些集内运行的任务。这主要用于大型SMP或NUMA系统。

* CONFIG_X86_CPU_RESCTRL

```
config X86_CPU_RESCTRL
	bool "x86 CPU resource control support"
	depends on X86 && (CPU_SUP_INTEL || CPU_SUP_AMD)
	select KERNFS
	select PROC_CPU_RESCTRL		if PROC_FS
	help
	  Enable x86 CPU resource control support.

	  Provide support for the allocation and monitoring of system resources
	  usage by the CPU.

	  Intel calls this Intel Resource Director Technology
	  (Intel(R) RDT). More information about RDT can be found in the
	  Intel x86 Architecture Software Developer Manual.

	  AMD calls this AMD Platform Quality of Service (AMD QoS).
	  More information about AMD QoS can be found in the AMD64 Technology
	  Platform Quality of Service Extensions manual.

	  Say N if unsure.
```

启用x86 CPU资源控制支持。为CPU使用系统资源的分配和监控提供支持。

英特尔称之为英特尔资源总监技术(英特尔(R) RDT)。关于RDT的更多信息可以在Intel x86架构软件开发人员手册中找到。

AMD将此称为AMD平台服务质量(AMD QoS)。有关AMD QoS的更多信息可以在AMD64技术平台服务质量扩展手册中找到。

* CONFIG_FUTEX

```
config FUTEX
	bool "Enable futex support" if EXPERT
	depends on !(SPARC32 && SMP)
	default y
	imply RT_MUTEXES
	help
	  Disabling this option will cause the kernel to be built without
	  support for "fast userspace mutexes".  The resulting kernel may not
	  run glibc-based applications correctly.
```

禁用此选项将导致内核在构建时不支持“快速用户空间互斥”。生成的内核可能无法正确运行基于glibc的应用程序。

* CONFIG_PERF_EVENTS

```
config PERF_EVENTS
	bool "Kernel performance events and counters"
	default y if PROFILING
	depends on HAVE_PERF_EVENTS
	select IRQ_WORK
	help
	  Enable kernel support for various performance events provided
	  by software and hardware.

	  Software events are supported either built-in or via the
	  use of generic tracepoints.

	  Most modern CPUs support performance events via performance
	  counter registers. These registers count the number of certain
	  types of hw events: such as instructions executed, cachemisses
	  suffered, or branches mis-predicted - without slowing down the
	  kernel or applications. These registers can also trigger interrupts
	  when a threshold number of events have passed - and can thus be
	  used to profile the code that runs on that CPU.

	  The Linux Performance Event subsystem provides an abstraction of
	  these software and hardware event capabilities, available via a
	  system call and used by the "perf" utility in tools/perf/. It
	  provides per task and per CPU counters, and it provides event
	  capabilities on top of those.

	  Say Y if unsure.
```

为软件和硬件提供的各种性能事件启用内核支持。

软件事件可以内置支持，也可以通过使用通用跟踪点来支持。

大多数现代cpu通过性能计数器寄存器支持性能事件。这些寄存器统计特定类型的hw事件的数量:例如执行的指令、遭受的缓存或错误预测的分支，而不会减慢内核或应用程序的速度。这些寄存器还可以在事件数量达到阈值时触发中断——因此可以用来分析在该CPU上运行的代码。

Linux性能事件子系统提供了这些软件和硬件事件功能的抽象，可以通过系统调用获得，并由tools/perf/中的“perf”实用程序使用。它提供了每个任务和每个CPU计数器，并在这些计数器之上提供了事件功能。

* CONFIG_DEBUG_PREEMPT

```
config DEBUG_PREEMPT
	bool "Debug preemptible kernel"
	depends on DEBUG_KERNEL && PREEMPTION && TRACE_IRQFLAGS_SUPPORT
	help
	  If you say Y here then the kernel will use a debug variant of the
	  commonly used smp_processor_id() function and will print warnings
	  if kernel code uses it in a preemption-unsafe way. Also, the kernel
	  will detect preemption count underflows.

	  This option has potential to introduce high runtime overhead,
	  depending on workload as it triggers debugging routines for each
	  this_cpu operation. It should only be used for debugging purposes.
```

调试可抢占内核

* CONFIG_NUMA

```
config NUMA
	bool "NUMA Memory Allocation and Scheduler Support"
	depends on SMP
	depends on X86_64 || (X86_32 && HIGHMEM64G && X86_BIGSMP)
	default y if X86_BIGSMP
	select USE_PERCPU_NUMA_NODE_ID
	help
	  Enable NUMA (Non-Uniform Memory Access) support.

	  The kernel will try to allocate memory used by a CPU on the
	  local memory controller of the CPU and add some more
	  NUMA awareness to the kernel.

	  For 64-bit this is recommended if the system is Intel Core i7
	  (or later), AMD Opteron, or EM64T NUMA.

	  For 32-bit this is only needed if you boot a 32-bit
	  kernel on a 64-bit NUMA platform.

	  Otherwise, you should say N.
```

启用NUMA(非统一内存访问)支持。

* CONFIG_NUMA_BALANCING

```
config NUMA_BALANCING
	bool "Memory placement aware NUMA scheduler"
	depends on ARCH_SUPPORTS_NUMA_BALANCING
	depends on !ARCH_WANT_NUMA_VARIABLE_LOCALITY
	depends on SMP && NUMA && MIGRATION && !PREEMPT_RT
	help
	  This option adds support for automatic NUMA aware memory/task placement.
	  The mechanism is quite primitive and is based on migrating memory when
	  it has references to the node the task is running on.

	  This system will be inactive on UMA systems.
```

该选项增加了对自动NUMA感知内存/任务放置的支持。该机制非常原始，并且基于对运行任务的节点有引用时迁移内存。

* CONFIG_RSEQ

```
config RSEQ
	bool "Enable rseq() system call" if EXPERT
	default y
	depends on HAVE_RSEQ
	select MEMBARRIER
	help
	  Enable the restartable sequences system call. It provides a
	  user-space cache for the current CPU number value, which
	  speeds up getting the current CPU number from user-space,
	  as well as an ABI to speed up user-space operations on
	  per-CPU data.

	  If unsure, say Y.
```

启用可重启序列系统调用。它为当前CPU数值提供了一个用户空间缓存，从而加快了从用户空间获取当前CPU数值的速度，还提供了一个ABI来加快用户空间对每个CPU数据的操作。

* CONFIG_SCHED_MM_CID

```
config SCHED_MM_CID
	def_bool y
	depends on SMP && RSEQ
```

* CONFIG_TASK_DELAY_ACCT

```
config TASK_DELAY_ACCT
	bool "Enable per-task delay accounting"
	depends on TASKSTATS
	select SCHED_INFO
	help
	  Collect information on time spent by a task waiting for system
	  resources like cpu, synchronous block I/O completion and swapping
	  in pages. Such statistics can help in setting a task's priorities
	  relative to other tasks for cpu, io, rss limits etc.

	  Say N if unsure.
```

收集任务等待系统资源(如cpu、同步块I/O完成和页面交换)所花费的时间信息。这样的统计数据可以帮助设置任务相对于其他任务的优先级，如cpu、io、rss限制等。

* CONFIG_FAULT_INJECTION

```
config F2FS_FAULT_INJECTION
	bool "F2FS fault injection facility"
	depends on F2FS_FS
	help
	  Test F2FS to inject faults such as ENOMEM, ENOSPC, and so on.

	  If unsure, say N.

```

测试F2FS注入错误，如ENOMEM、ENOSPC等。

* CONFIG_LATENCYTOP

```
config LATENCYTOP
	bool "Latency measuring infrastructure"
	depends on DEBUG_KERNEL
	depends on STACKTRACE_SUPPORT
	depends on PROC_FS
	depends on FRAME_POINTER || MIPS || PPC || S390 || MICROBLAZE || ARM || ARC || X86
	select KALLSYMS
	select KALLSYMS_ALL
	select STACKTRACE
	select SCHEDSTATS
	help
	  Enable this option if you want to use the LatencyTOP tool
	  to find out which userspace is blocking on what kernel operations.
```

如果您希望使用LatencyTOP工具来查找哪个用户空间阻塞了哪些内核操作，请启用此选项。

* CONFIG_KASAN_GENERIC

```
config KASAN_GENERIC
	bool "Generic KASAN"
	depends on HAVE_ARCH_KASAN && CC_HAS_KASAN_GENERIC
	depends on CC_HAS_WORKING_NOSANITIZE_ADDRESS
	select SLUB_DEBUG if SLUB
	select CONSTRUCTORS
	help
	  Enables Generic KASAN.

	  Requires GCC 8.3.0+ or Clang.

	  Consumes about 1/8th of available memory at kernel start and adds an
	  overhead of ~50% for dynamic allocations.
	  The performance slowdown is ~x3.

	  (Incompatible with CONFIG_DEBUG_SLAB: the kernel does not boot.)
```

* CONFIG_KCSAN

```
menuconfig KCSAN
	bool "KCSAN: dynamic data race detector"
	depends on HAVE_ARCH_KCSAN && HAVE_KCSAN_COMPILER
	depends on DEBUG_KERNEL && !KASAN
	select CONSTRUCTORS
	select STACKTRACE
	help
	  The Kernel Concurrency Sanitizer (KCSAN) is a dynamic
	  data-race detector that relies on compile-time instrumentation.
	  KCSAN uses a watchpoint-based sampling approach to detect races.

	  While KCSAN's primary purpose is to detect data races, it
	  also provides assertions to check data access constraints.
	  These assertions can expose bugs that do not manifest as
	  data races.

	  See <file:Documentation/dev-tools/kcsan.rst> for more details.

```

内核并发消毒器(KCSAN)是一种依赖于编译时检测的动态数据竞争检测器。KCSAN使用基于观察点的抽样方法来检测竞争。

虽然KCSAN的主要目的是检测数据竞争，但它也提供断言来检查数据访问约束。这些断言可以暴露不表现为数据竞争的错误。

* CONFIG_KMSAN

```
config KMSAN
	bool "KMSAN: detector of uninitialized values use"
	depends on HAVE_ARCH_KMSAN && HAVE_KMSAN_COMPILER
	depends on SLUB && DEBUG_KERNEL && !KASAN && !KCSAN
	depends on !PREEMPT_RT
	select STACKDEPOT
	select STACKDEPOT_ALWAYS_INIT
	help
	  KernelMemorySanitizer (KMSAN) is a dynamic detector of uses of
	  uninitialized values in the kernel. It is based on compiler
	  instrumentation provided by Clang and thus requires Clang to build.

	  An important note is that KMSAN is not intended for production use,
	  because it drastically increases kernel memory footprint and slows
	  the whole system down.

	  See <file:Documentation/dev-tools/kmsan.rst> for more details.
```

kernelmemorysaniizer (KMSAN)是一个动态检测器，用于检测内核中未初始化值的使用情况。

它基于Clang提供的编译器工具，因此需要Clang来构建。需要注意的是，KMSAN不适合用于生产环境，因为它会极大地增加内核内存占用并降低整个系统的速度。

* IS_ENABLED(CONFIG_KUNIT)

```
menuconfig KUNIT
	tristate "KUnit - Enable support for unit tests"
	select GLOB if KUNIT=y
	help
	  Enables support for kernel unit tests (KUnit), a lightweight unit
	  testing and mocking framework for the Linux kernel. These tests are
	  able to be run locally on a developer's workstation without a VM or
	  special hardware when using UML. Can also be used on most other
	  architectures. For more information, please see
	  Documentation/dev-tools/kunit/.
```

支持内核单元测试(KUnit)，这是一个用于Linux内核的轻量级单元测试和模拟框架。当使用UML时，这些测试能够在开发人员的工作站上本地运行，而不需要VM或特殊硬件。也可以在大多数其他架构上使用。更多信息，请参见Documentation/dev-tools/kunit/。

* CONFIG_FUNCTION_GRAPH_TRACER

```
config FUNCTION_GRAPH_TRACER
	bool "Kernel Function Graph Tracer"
	depends on HAVE_FUNCTION_GRAPH_TRACER
	depends on FUNCTION_TRACER
	depends on !X86_32 || !CC_OPTIMIZE_FOR_SIZE
	default y
	help
	  Enable the kernel to trace a function at both its return
	  and its entry.
	  Its first purpose is to trace the duration of functions and
	  draw a call graph for each thread with some information like
	  the return value. This is done by setting the current return
	  address on the current task structure into a stack of calls.
```

使内核能够在函数的返回和入口处跟踪函数。

它的第一个目的是跟踪函数的持续时间，并为每个线程绘制带有返回值等信息的调用图。这是通过将当前任务结构上的当前返回地址设置为调用堆栈来实现的。

* CONFIG_TRACING

```
config TRACING
	bool
	select RING_BUFFER
	select STACKTRACE if STACKTRACE_SUPPORT
	select TRACEPOINTS
	select NOP_TRACER
	select BINARY_PRINTF
	select EVENT_TRACING
	select TRACE_CLOCK
	select TASKS_RCU if PREEMPTION
```

* CONFIG_KCOV

```
config KCOV
	bool "Code coverage for fuzzing"
	depends on ARCH_HAS_KCOV
	depends on CC_HAS_SANCOV_TRACE_PC || GCC_PLUGINS
	depends on !ARCH_WANTS_NO_INSTR || HAVE_NOINSTR_HACK || \
		   GCC_VERSION >= 120000 || CLANG_VERSION >= 130000
	select DEBUG_FS
	select GCC_PLUGIN_SANCOV if !CC_HAS_SANCOV_TRACE_PC
	select OBJTOOL if HAVE_NOINSTR_HACK
	help
	  KCOV exposes kernel code coverage information in a form suitable
	  for coverage-guided fuzzing (randomized testing).

	  If RANDOMIZE_BASE is enabled, PC values will not be stable across
	  different machines and across reboots. If you need stable PC values,
	  disable RANDOMIZE_BASE.

	  For more details, see Documentation/dev-tools/kcov.rst.
```

KCOV以一种适合于覆盖率引导的模糊测试(随机测试)的形式公开内核代码覆盖率信息。

如果启用了RANDOMIZE_BASE, PC值在不同的机器和重新启动时将不稳定。如果你需要稳定的PC值，禁用RANDOMIZE_BASE。

* CONFIG_MEMCG

```
config MEMCG
	bool "Memory controller"
	select PAGE_COUNTER
	select EVENTFD
	help
	  Provides control over the memory footprint of tasks in a cgroup.
```

提供对c组中任务的内存占用的控制。

* CONFIG_UPROBES

```
config UPROBES
	def_bool n
	depends on ARCH_SUPPORTS_UPROBES
	help
	  Uprobes is the user-space counterpart to kprobes: they
	  enable instrumentation applications (such as 'perf probe')
	  to establish unintrusive probes in user-space binaries and
	  libraries, by executing handler functions when the probes
	  are hit by user-space applications.

	  ( These probes come in the form of single-byte breakpoints,
	    managed by the kernel and kept transparent to the probed
	    application. )
```

Uprobes是kprobes的用户空间对应物:它们使仪表应用程序(如'perf probe')能够在用户空间二进制文件和库中建立非侵入式探测，方法是在探测被用户空间应用程序击中时执行处理程序函数。

(这些探测以单字节断点的形式出现，由内核管理，对被探测的应用程序保持透明。)

* CONFIG_BCACHE

```
config BCACHE
	tristate "Block device as cache"
	select BLOCK_HOLDER_DEPRECATED if SYSFS
	select CRC64
	help
	Allows a block device to be used as cache for other devices; uses
	a btree for indexing and the layout is optimized for SSDs.

	See Documentation/admin-guide/bcache.rst for details.
```

允许一个块设备用作其他设备的缓存;使用b树进行索引，布局针对ssd进行了优化。

* CONFIG_MMU

```
config MMU
	def_bool y
```

* CONFIG_VMAP_STACK

```
config VMAP_STACK
	default y
	bool "Use a virtually-mapped stack"
	depends on HAVE_ARCH_VMAP_STACK
	depends on !KASAN || KASAN_HW_TAGS || KASAN_VMALLOC
	help
	  Enable this if you want the use virtually-mapped kernel stacks
	  with guard pages.  This causes kernel stack overflows to be
	  caught immediately rather than causing difficult-to-diagnose
	  corruption.

	  To use this with software KASAN modes, the architecture must support
	  backing virtual mappings with real shadow memory, and KASAN_VMALLOC
	  must be enabled.
```

如果您希望使用带有保护页的虚拟映射内核堆栈，请启用此选项。这将导致立即捕获内核堆栈溢出，而不是导致难以诊断的损坏。

为了在软件KASAN模式中使用它，架构必须支持使用真实影子内存的虚拟映射，并且KASAN_VMALLOC必须启用。

* CONFIG_LIVEPATCH

```
config LIVEPATCH
	bool "Kernel Live Patching"
	depends on DYNAMIC_FTRACE_WITH_REGS || DYNAMIC_FTRACE_WITH_ARGS
	depends on MODULES
	depends on SYSFS
	depends on KALLSYMS_ALL
	depends on HAVE_LIVEPATCH
	depends on !TRIM_UNUSED_KSYMS
	help
	  Say Y here if you want to support kernel live patching.
	  This option has no runtime impact until a kernel "patch"
	  module uses the interface provided by this option to register
	  a patch, causing calls to patched functions to be redirected
	  to new function code contained in the patch module.
```

如果您希望支持内核实时补丁，请在这里输入Y。该选项对运行时没有影响，直到内核“补丁”模块使用该选项提供的接口注册补丁，导致对补丁函数的调用被重定向到补丁模块中包含的新函数代码。

* CONFIG_SECURITY

```
config SECURITY
	bool "Enable different security models"
	depends on SYSFS
	depends on MULTIUSER
	help
	  This allows you to choose different security modules to be
	  configured into your kernel.

	  If this option is not selected, the default Linux security
	  model will be used.

	  If you are unsure how to answer this question, answer N.
```

这允许您选择要配置到内核中的不同安全模块。如果不选择此选项，则将使用默认的Linux安全模型。

* CONFIG_BPF_SYSCALL

```
config BPF_SYSCALL
	bool "Enable bpf() system call"
	select BPF
	select IRQ_WORK
	select TASKS_RCU if PREEMPTION
	select TASKS_TRACE_RCU
	select BINARY_PRINTF
	select NET_SOCK_MSG if NET
	select PAGE_POOL if NET
	default n
	help
	  Enable the bpf() system call that allows to manipulate BPF programs
	  and maps via file descriptors.
```

启用允许操作bpf程序的bpf系统调用并通过文件描述符映射。

* CONFIG_GCC_PLUGIN_STACKLEAK

```
config GCC_PLUGIN_STACKLEAK
	bool "Poison kernel stack before returning from syscalls"
	depends on GCC_PLUGINS
	depends on HAVE_ARCH_STACKLEAK
	help
	  This option makes the kernel erase the kernel stack before
	  returning from system calls. This has the effect of leaving
	  the stack initialized to the poison value, which both reduces
	  the lifetime of any sensitive stack contents and reduces
	  potential for uninitialized stack variable exploits or information
	  exposures (it does not cover functions reaching the same stack
	  depth as prior functions during the same syscall). This blocks
	  most uninitialized stack variable attacks, with the performance
	  impact being driven by the depth of the stack usage, rather than
	  the function calling complexity.

	  The performance impact on a single CPU system kernel compilation
	  sees a 1% slowdown, other systems and workloads may vary and you
	  are advised to test this feature on your expected workload before
	  deploying it.

	  This plugin was ported from grsecurity/PaX. More information at:
	   * https://grsecurity.net/
	   * https://pax.grsecurity.net/
```

该选项使内核在从系统调用返回之前擦除内核堆栈。这样做的效果是使堆栈初始化为有毒值，这既减少了任何敏感堆栈内容的生命周期，又减少了未初始化堆栈变量被利用或信息暴露的可能性(它不包括在同一系统调用期间达到与先前函数相同堆栈深度的函数)。这将阻止大多数未初始化的堆栈变量攻击，其性能影响取决于堆栈使用的深度，而不是函数调用的复杂性。

对单个CPU系统内核编译的性能影响会降低1%，其他系统和工作负载可能会有所不同，建议您在部署该特性之前在预期的工作负载上测试该特性。

* CONFIG_X86_MCE

```
config X86_MCE
	bool "Machine Check / overheating reporting"
	select GENERIC_ALLOCATOR
	default y
	help
	  Machine Check support allows the processor to notify the
	  kernel if it detects a problem (e.g. overheating, data corruption).
	  The action the kernel takes depends on the severity of the problem,
	  ranging from warning messages to halting the machine.
```

机器检查支持允许处理器通知内核，如果它检测到一个问题(例如过热，数据损坏)。内核采取的操作取决于问题的严重程度，从警告消息到停止机器。

* CONFIG_KRETPROBES

```
config KRETPROBES
	def_bool y
	depends on KPROBES && (HAVE_KRETPROBES || HAVE_RETHOOK)
```

* CONFIG_RETHOOK

```
config RETHOOK
	bool
	depends on HAVE_RETHOOK
	help
	  Enable generic return hooking feature. This is an internal
	  API, which will be used by other function-entry hooking
	  features like fprobe and kprobes.
```

启用泛型返回挂钩特性。这是一个内部API，其他函数入口挂钩特性(如fprobe和kprobes)将使用它。。

* CONFIG_ARCH_HAS_PARANOID_L1D_FLUSH

```
config ARCH_HAS_PARANOID_L1D_FLUSH
	bool
```

* CONFIG_RV

```
menuconfig RV
	bool "Runtime Verification"
	depends on TRACING
	help
	  Enable the kernel runtime verification infrastructure. RV is a
	  lightweight (yet rigorous) method that complements classical
	  exhaustive verification techniques (such as model checking and
	  theorem proving). RV works by analyzing the trace of the system's
	  actual execution, comparing it against a formal specification of
	  the system behavior.

	  For further information, see:
	    Documentation/trace/rv/runtime-verification.rst
```

启用内核运行时验证基础结构。RV是一种轻量级(但严格的)方法，它补充了经典的详尽验证技术(如模型检查和定理证明)。RV的工作原理是分析系统实际执行的跟踪，并将其与系统行为的正式规范进行比较。

* CONFIG_USER_EVENTS

```
config USER_EVENTS
	bool "User trace events"
	select TRACING
	select DYNAMIC_EVENTS
	help
	  User trace events are user-defined trace events that
	  can be used like an existing kernel trace event.  User trace
	  events are generated by writing to a tracefs file.  User
	  processes can determine if their tracing events should be
	  generated by registering a value and bit with the kernel
	  that reflects when it is enabled or not.

	  See Documentation/trace/user_events.rst.
	  If in doubt, say N.
```

用户跟踪事件是用户定义的跟踪事件，可以像使用现有的内核跟踪事件一样使用。用户跟踪事件是通过写入tracefs文件生成的。用户进程可以通过向内核注册反映何时启用或不启用的值和位来确定是否应该生成它们的跟踪事件。

### 进程状态 Process State

### 标识一个进程 Identifying a Process

#### 进程描述符处理 Process descriptors handling

#### 标识当前进程 Identifying the current process

#### 双向链表 Doubly linked lists

#### 进程链表 The process list

#### TASK_RUNNING状态的进程链表 The lists of TASK_RUNNING Processes

### 进程间的关系 Relationships Among Processes

#### pidhash表及链表 The pidhash table and chained lists

### 如何组织进程 How Processes Are Organized

#### 等待队列 Wait queues

#### 等待队列的操作 Handling wait queues

### 进程资源限制 Process Resource Limits

## 进程切换 Process Switch

### 硬件上下文 Hardware Context

### 任务状态栏 Task State Segment

#### thread字段 The thread field

### 执行进程切换 Performing the Process Switch

#### switch_to宏 The switch_to macro

#### __switch_to()函数 The __switch_to() function

### 保存和加载FPU、MMX及XMM寄存器 Saving and Loading the FPU,MMX,and XMM Registers

#### 保存FPU寄存器 Saving the FPU registers

#### 装载FPU寄存器 Loading the FPU registers

#### 在内核态使用FPU、MMX和SSE/SSE2单元 Using the FPU,MMX,and SSE/SSE2 units in Kernel Mode

## 创建进程 Creating Processes

### clone()、fork()及vfork()系统调用 The clone(),fork(),and vfork() System Calls

#### do_fork()函数 The do_fork() function

#### copy_process()函数 The copy_process() function

### 内核线程 Kernel Threads

#### 创建一个内核线程 Creating a kernel thread

#### 进程0 Process 0

#### 进程1 Process 1

#### 其他内核线程 Other kernel threads

## 撤销进程 Destroying Processes

### 进程终止 Process Termination

#### do_group_exit()函数 The do_group_exit() function

#### do_exit()函数 The do_exit() function

### 进程删除 Process Removal
