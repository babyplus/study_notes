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
