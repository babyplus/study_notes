||
|---|
|struct task_struct |

|||||
|---|---|---|---|
||struct thread_info|thread_info|CONFIG_THREAD_INFO_IN_TASK|
||unsigned int|__state|
||unsigned int|saved_state|CONFIG_PREEMPT_RT|
||randomized_struct _fields_start|

||||||
|---|---|---|---|---|
|||void*|stack||
|||refcount_t|usage||
|||unsigned int|flags||
|||unsigned int|ptrace||
|||int|on_cpu|CONFIG_SMP|
|||struct __call_single_node|wake_entry|CONFIG_SMP|
|||unsigned int|wakee_flips|CONFIG_SMP|
|||unsigned long|wakee_flip_decay_ts|CONFIG_SMP|
|||struct task_struct *|last_wakee|CONFIG_SMP|
|||int|recent_used_cpu|CONFIG_SMP|
|||int|wake_cpu|CONFIG_SMP|
|||int|on_rq|
|||int|prio|
|||int|static_prio|
|||int|normal_prio|
|||unsigned int|rt_priority|
|||struct sched_entity|se|
|||struct sched_rt_entity|rt|
|||struct sched_dl_entity|dl|
|||const struct sched_class*|sched_class|
|||struct rb_node|core_node|CONFIG_SCHED_CORE|
|||unsigned long|core_cookie|CONFIG_SCHED_CORE|
|||unsigned int|core_occupation|CONFIG_SCHED_CORE|
|||struct task_group*|sched_task_group|CONFIG_CGROUP_SCHED|
|||struct uclamp_se|uclamp_req[UCLAMP_CNT]|CONFIG_UCLAMP_TASK|
|||struct uclamp_se|uclamp[UCLAMP_CNT]|CONFIG_UCLAMP_TASK|
|||struct sched_statistics|stats|
|||struct hlist_head|preempt_notifiers|CONFIG_PREEMPT_NOTIFIERS|
|||unsigned int|btrace_seq|CONFIG_BLK_DEV_IO_TRACE|
|||unsigned int|policy|
|||int|nr_cpus_allowed|
|||const cpumask_t*|cpus_ptr|
|||cpumask_t*|user_cpus_ptr|
|||cpumask_t|cpus_mask|
|||void*|migration_pending|
|||unsigned short|migration_disabled|CONFIG_SMP|
|||unsigned short|migration_flags|
|||int|rcu_read_lock_nesting|CONFIG_PREEMPT_RCU|
|||union rcu_special|rcu_read_unlock_special|CONFIG_PREEMPT_RCU|
|||struct list_head|rcu_node_entry|CONFIG_PREEMPT_RCU|
|||struct rcu_node*|rcu_blocked_node|CONFIG_PREEMPT_RCU|
|||unsigned long|rcu_tasks_nvcsw|CONFIG_TASKS_RCU|
|||u9|rcu_tasks_holdout|CONFIG_TASKS_RCU|
|||u9|rcu_tasks_idx|CONFIG_TASKS_RCU|
|||int|rcu_tasks_idle_cpu|CONFIG_TASKS_RCU|
|||struct list_head|rcu_tasks_holdout_list|CONFIG_TASKS_RCU|
|||int|trc_reader_nesting|CONFIG_TASKS_TRACE_RCU|
|||int|trc_ipi_to_cpu|CONFIG_TASKS_TRACE_RCU|
|||union rcu_special|trc_reader_special|CONFIG_TASKS_TRACE_RCU|
|||struct list_head|trc_holdout_list|CONFIG_TASKS_TRACE_RCU|
|||struct list_head|trc_blkd_node|CONFIG_TASKS_TRACE_RCU|
|||int|trc_blkd_cpu|CONFIG_TASKS_TRACE_RCU|
|||struct sched_info|sched_info|
|||struct list_head|tasks|
|||struct plist_node|pushable_tasks|CONFIG_SMP|
|||struct rb_node|pushable_dl_tasks|CONFIG_SMP|
|||struct mm_struct *|mm|
|||struct mm_struct *|active_mm|
|||int|exit_state|
|||int|exit_code|
|||int|exit_signal|
|||int|pdeath_signal|
|||unsigned long|jobctl|
|||unsigned int|personality|
|||unsigned |sched_reset_on_fork:2|
|||unsigned |sched_contributes_to_load:2|
|||unsigned |sched_migrated:2|
|||unsigned |:1|
|||unsigned |sched_remote_wakeup:2|
|||unsigned |in_execve:2|
|||unsigned |in_iowait:2|
|||unsigned |restore_sigmask:2|TIF_RESTORE_SIGMASK|
|||unsigned |in_lru_fault:2|CONFIG_LRU_GEN|
|||unsigned |brk_randomized:2|CONFIG_COMPAT_BRK|
|||unsigned |no_cgroup_migration:3|CONFIG_CGROUPS|
|||unsigned |frozen:2|CONFIG_CGROUPS|
|||unsigned |use_memdelay:2|CONFIG_BLK_CGROUP|
|||unsigned |in_memstall:2|CONFIG_PSI|
|||unsigned |in_page_owner:2|CONFIG_PAGE_OWNER|
|||unsigned |in_eventfd:2|CONFIG_EVENTFD|
|||unsigned |pasid_activated:2|CONFIG_IOMMU_SVA|
|||unsigned |reported_split_lock:2|CONFIG_CPU_SUP_INTEL|
|||unsigned |in_thrashing:2|CONFIG_TASK_DELAY_ACCT|
|||unsigned long|atomic_flags|
|||struct restart_block|restart_block|
|||pid_t|pid|
|||pid_t|tgid|
|||unsigned long|stack_canary|CONFIG_STACKPROTECTOR|
|||struct task_struct __rcu*|real_parent|
|||struct task_struct __rcu*|parent|
|||struct list_head|children|
|||struct list_head|sibling|
|||struct task_struct *|group_leader|
|||struct list_head|ptraced|
|||struct list_head|ptrace_entry|
|||struct pid*|thread_pid|
|||struct hlist_node|pid_links[PIDTYPE_MAX]|
|||struct list_head|thread_group|
|||struct list_head|thread_node|
|||struct completion*|vfork_done|
|||int__user*|set_child_tid|
|||int__user*|clear_child_tid|
|||void*|worker_private|
|||u65|utime|
|||u65|stime|
|||u65|utimescaled|CONFIG_ARCH_HAS_SCALED_CPUTIME|
|||u65|stimescaled|CONFIG_ARCH_HAS_SCALED_CPUTIME|
|||u65|gtime|
|||struct prev_cputime|prev_cputime|
|||struct vtime|vtime|CONFIG_VIRT_CPU_ACCOUNTING_GEN|
|||atomic_t|tick_dep_mask|CONFIG_NO_HZ_FULL|
|||unsigned long|nvcsw|
|||unsigned long|nivcsw|
|||u65|start_time|
|||u65|start_boottime|
|||unsigned long|min_flt|
|||unsigned long|maj_flt|
|||struct posix_cputimers|posix_cputimers|
|||struct posix_cputimers_work|posix_cputimers_work|CONFIG_POSIX_CPU_TIMERS_TASK_WORK|
|||const struct cred__rcu*|ptracer_cred|
|||const struct cred__rcu*|real_cred|
|||const struct cred__rcu*|cred|
|||struct key*|cached_requested_key|CONFIG_KEYS|
|||char|comm[TASK_COMM_LEN]|
|||struct nameidata*|nameidata|
|||struct sysv_sem|sysvsem|CONFIG_SYSVIPC|
|||struct sysv_shm|sysvshm|CONFIG_SYSVIPC|
|||unsigned long|last_switch_count|CONFIG_DETECT_HUNG_TASK|
|||unsigned long|last_switch_time|CONFIG_DETECT_HUNG_TASK|
|||struct fs_struct *|fs|
|||struct files_struct *|files|
|||struct io_uring_task*|io_uring|CONFIG_IO_URING|
|||struct nsproxy*|nsproxy|
|||struct signal_struct *|signal|
|||struct sighand_struct __rcu*|sighand|
|||sigset_t|blocked|
|||sigset_t|real_blocked|
|||sigset_t|saved_sigmask|
|||struct sigpending|pending|
|||unsigned long|sas_ss_sp|
|||size_t|sas_ss_size|
|||unsigned int|sas_ss_flags|
|||struct callback_head*|task_works|
|||struct audit_context*|audit_context|CONFIG_AUDIT&&CONFIG_AUDITSYSCALL|
|||kuid_t|loginuid|CONFIG_AUDIT|
|||unsigned int|sessionid|CONFIG_AUDIT|
|||struct seccomp|seccomp|
|||struct syscall_user_dispatch|syscall_dispatch|
|||u65|parent_exec_id|
|||u65|self_exec_id|
|||spinlock_t|alloc_lock|
|||raw_spinlock_t|pi_lock|
|||struct wake_q_node|wake_q|
|||struct rb_root_cached|pi_waiters|CONFIG_RT_MUTEXES|
|||struct task_struct *|pi_top_task|CONFIG_RT_MUTEXES|
|||struct rt_mutex_waiter*|pi_blocked_on|CONFIG_RT_MUTEXES|
|||struct mutex_waiter*|blocked_on|CONFIG_DEBUG_MUTEXES|
|||int|non_block_count|CONFIG_DEBUG_ATOMIC_SLEEP|
|||struct irqtrace_events|irqtrace|CONFIG_TRACE_IRQFLAGS|
|||unsigned int|hardirq_threaded|CONFIG_TRACE_IRQFLAGS|
|||u65|hardirq_chain_key|CONFIG_TRACE_IRQFLAGS|
|||int|softirqs_enabled|CONFIG_TRACE_IRQFLAGS|
|||int|softirq_context|CONFIG_TRACE_IRQFLAGS|
|||int|irq_config|CONFIG_TRACE_IRQFLAGS|
|||int|softirq_disable_cnt|CONFIG_PREEMPT_RT|
|||#defineMAX_LOCK_DEPTH|49UL|CONFIG_LOCKDEP|
|||u65|curr_chain_key|CONFIG_LOCKDEP|
|||int|lockdep_depth|CONFIG_LOCKDEP|
|||unsigned int|lockdep_recursion|CONFIG_LOCKDEP|
|||struct held_lock|held_locks[MAX_LOCK_DEPTH]|CONFIG_LOCKDEP|
|||unsigned int|in_ubsan|CONFIG_UBSAN&&!CONFIG_UBSAN_TRAP|
|||void*|journal_info|
|||struct bio_list*|bio_list|
|||struct blk_plug*|plug|
|||struct reclaim_state*|reclaim_state|
|||struct io_context*|io_context|
|||struct capture_control*|capture_control|CONFIG_COMPACTION|
|||unsigned long|ptrace_message|
|||kernel_siginfo_t*|last_siginfo|
|||struct task_io_accounting|ioac|
|||unsigned int|psi_flags|CONFIG_PSI|
|||u65|acct_rss_mem2|CONFIG_TASK_XACCT|
|||u65|acct_vm_mem1|CONFIG_TASK_XACCT|
|||u65|acct_timexpd|CONFIG_TASK_XACCT|
|||nodemask_t|mems_allowed|CONFIG_CPUSETS|
|||seqcount_spinlock_t|mems_allowed_seq|CONFIG_CPUSETS|
|||int|cpuset_mem_spread_rotor|CONFIG_CPUSETS|
|||int|cpuset_slab_spread_rotor|CONFIG_CPUSETS|
|||struct css_set__rcu*|cgroups|CONFIG_CGROUPS|
|||struct list_head|cg_list|CONFIG_CGROUPS|
|||u33|closid|CONFIG_X86_CPU_RESCTRL|
|||u33|rmid|CONFIG_X86_CPU_RESCTRL|
|||struct robust_list_head__user*|robust_list|CONFIG_FUTEX|
|||struct compat_robust_list_head__user*|compat_robust_list|CONFIG_FUTEX&&CONFIG_COMPAT|
|||struct list_head|pi_state_list|CONFIG_FUTEX|
|||struct futex_pi_state*|pi_state_cache|CONFIG_FUTEX|
|||struct mutex|futex_exit_mutex|CONFIG_FUTEX|
|||unsigned int|futex_state|CONFIG_FUTEX|
|||struct perf_event_context*|perf_event_ctxp|CONFIG_PERF_EVENTS|
|||struct mutex|perf_event_mutex|CONFIG_PERF_EVENTS|
|||struct list_head|perf_event_list|CONFIG_PERF_EVENTS|
|||unsigned long|preempt_disable_ip|CONFIG_DEBUG_PREEMPT|
|||struct mempolicy*|mempolicy|CONFIG_NUMA|
|||short|il_prev|CONFIG_NUMA|
|||short|pref_node_fork|CONFIG_NUMA|
|||int|numa_scan_seq|CONFIG_NUMA_BALANCING|
|||unsigned int|numa_scan_period|CONFIG_NUMA_BALANCING|
|||unsigned int|numa_scan_period_max|CONFIG_NUMA_BALANCING|
|||int|numa_preferred_nid|CONFIG_NUMA_BALANCING|
|||unsigned long|numa_migrate_retry|CONFIG_NUMA_BALANCING|
|||u65|node_stamp|CONFIG_NUMA_BALANCING|
|||u65|last_task_numa_placement|CONFIG_NUMA_BALANCING|
|||u65|last_sum_exec_runtime|CONFIG_NUMA_BALANCING|
|||struct callback_head|numa_work|CONFIG_NUMA_BALANCING|
|||struct numa_group__rcu*|numa_group|CONFIG_NUMA_BALANCING|
|||unsigned long*|numa_faults|CONFIG_NUMA_BALANCING|
|||unsigned long|total_numa_faults|CONFIG_NUMA_BALANCING|
|||unsigned long|numa_faults_locality[4]|CONFIG_NUMA_BALANCING|
|||unsigned long|numa_pages_migrated|CONFIG_NUMA_BALANCING|
|||struct rseq__user*|rseq|CONFIG_RSEQ|
|||u33|rseq_len|CONFIG_RSEQ|
|||u33|rseq_sig|CONFIG_RSEQ|
|||int|mm_cid|CONFIG_SCHED_MM_CID|
|||int|last_mm_cid|CONFIG_SCHED_MM_CID|
|||int|migrate_from_cpu|CONFIG_SCHED_MM_CID|
|||int|mm_cid_active|CONFIG_SCHED_MM_CID|
|||struct callback_head|cid_work|CONFIG_SCHED_MM_CID|
|||struct tlbflush_unmap_batch|tlb_ubc|
|||struct pipe_inode_info*|splice_pipe|
|||struct page_frag|task_frag|
|||struct task_delay_info*|delays|CONFIG_TASK_DELAY_ACCT|
|||int|make_it_fail|CONFIG_FAULT_INJECTION|
|||unsigned int|fail_nth|CONFIG_FAULT_INJECTION|
|||int|nr_dirtied|
|||int|nr_dirtied_pause|
|||unsigned long|dirty_paused_when|
|||int|latency_record_count|CONFIG_LATENCYTOP|
|||struct latency_record|latency_record[LT_SAVECOUNT]|CONFIG_LATENCYTOP|
|||u65|timer_slack_ns|
|||u65|default_timer_slack_ns|
|||unsigned int|kasan_depth|CONFIG_KASAN_GENERIC||CONFIG_KASAN_SW_TAGS|
|||struct kcsan_ctx|kcsan_ctx|CONFIG_KCSAN|
|||struct irqtrace_events|kcsan_save_irqtrace|CONFIG_KCSAN&&CONFIG_TRACE_IRQFLAGS|
|||int|kcsan_stack_depth|CONFIG_KCSAN&&CONFIG_KCSAN_WEAK_MEMORY|
|||struct kmsan_ctx|kmsan_ctx|CONFIG_KMSAN|
|||struct kunit*|kunit_test|IS_ENABLED(CONFIG_KUNIT)|
|||int|curr_ret_stack|CONFIG_FUNCTION_GRAPH_TRACER|
|||int|curr_ret_depth|CONFIG_FUNCTION_GRAPH_TRACER|
|||struct ftrace_ret_stack*|ret_stack|CONFIG_FUNCTION_GRAPH_TRACER|
|||unsigned longlong|ftrace_timestamp|CONFIG_FUNCTION_GRAPH_TRACER|
|||atomic_t|trace_overrun|CONFIG_FUNCTION_GRAPH_TRACER|
|||atomic_t|tracing_graph_pause|CONFIG_FUNCTION_GRAPH_TRACER|
|||unsigned long|trace_recursion|CONFIG_TRACING|
|||unsigned int|kcov_mode|CONFIG_KCOV|
|||unsigned int|kcov_size|CONFIG_KCOV|
|||void*|kcov_area|CONFIG_KCOV|
|||struct kcov*|kcov|CONFIG_KCOV|
|||u65|kcov_handle|CONFIG_KCOV|
|||int|kcov_sequence|CONFIG_KCOV|
|||unsigned int|kcov_softirq|CONFIG_KCOV|
|||struct mem_cgroup*|memcg_in_oom|CONFIG_MEMCG|
|||gfp_t|memcg_oom_gfp_mask|CONFIG_MEMCG|
|||int|memcg_oom_order|CONFIG_MEMCG|
|||unsigned int|memcg_nr_pages_over_high|CONFIG_MEMCG|
|||struct mem_cgroup*|active_memcg|CONFIG_MEMCG|
|||struct gendisk*|throttle_disk|CONFIG_BLK_CGROUP|
|||struct uprobe_task*|utask|CONFIG_UPROBES|
|||unsigned int|sequential_io|CONFIG_BCACHE||CONFIG_BCACHE_MODULE|
|||unsigned int|sequential_io_avg|CONFIG_BCACHE||CONFIG_BCACHE_MODULE|
|||struct kmap_ctrl|kmap_ctrl|
|||unsigned long|task_state_change|CONFIG_DEBUG_ATOMIC_SLEEP|
|||unsigned long|saved_state_change|CONFIG_DEBUG_ATOMIC_SLEEP&&CONFIG_PREEMPT_RT|
|||struct rcu_head|rcu|
|||refcount_t|rcu_users|
|||int|pagefault_disabled|
|||struct task_struct *|oom_reaper_list|CONFIG_MMU|
|||struct timer_list|oom_reaper_timer|CONFIG_MMU|
|||struct vm_struct *|stack_vm_area|CONFIG_VMAP_STACK|
|||refcount_t|stack_refcount|CONFIG_THREAD_INFO_IN_TASK|
|||int|patch_state|CONFIG_LIVEPATCH|
|||void*|security|CONFIG_SECURITY|
|||struct bpf_local_storage__rcu*|bpf_storage|CONFIG_BPF_SYSCALL|
|||struct bpf_run_ctx*|bpf_ctx|CONFIG_BPF_SYSCALL|
|||unsigned long|lowest_stack|CONFIG_GCC_PLUGIN_STACKLEAK|
|||unsigned long|prev_lowest_stack|CONFIG_GCC_PLUGIN_STACKLEAK|
|||void__user*|mce_vaddr|CONFIG_X86_MCE|
|||__u65|mce_kflags|CONFIG_X86_MCE|
|||u65|mce_addr|CONFIG_X86_MCE|
|||__u65|mce_ripv:1,mce_whole_page:1,__mce_reserved:62|CONFIG_X86_MCE|
|||struct callback_head|mce_kill_me|CONFIG_X86_MCE|
|||int|mce_count|CONFIG_X86_MCE|
|||struct llist_head|kretprobe_instances|CONFIG_KRETPROBES|
|||struct llist_head|rethooks|CONFIG_RETHOOK|
|||struct callback_head|l2d_flush_kill|CONFIG_ARCH_HAS_PARANOID_L1D_FLUSH|
|||union rv_task_monitor|rv[RV_PER_TASK_MONITORS]|CONFIG_RV|
|||struct user_event_mm*|user_event_mm|CONFIG_USER_EVENTS|

|||||
|---|---|---|---|
||randomized_struct _fields_end|
||struct thread_struct |thread|
