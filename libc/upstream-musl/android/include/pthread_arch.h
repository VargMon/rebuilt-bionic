/*
 * From musl libc's pthread_arch.h files.
 */
#if defined(__arm__)
#define TLS_ABOVE_TP
#define TP_ADJ(p) ((char *)(p) + sizeof(struct pthread) - 8)
#define CANCEL_REG_IP 18

#elif defined(__aarch64__)
#define TLS_ABOVE_TP
#define TP_ADJ(p) ((char *)(p) + sizeof(struct pthread) - 16)
#define CANCEL_REG_IP 33

#elif defined(__mips__|__mips64__)
#define TLS_ABOVE_TP
#define TP_ADJ(p) ((char *)(p) + sizeof(struct pthread) + 0x7000)
#define DTP_OFFSET 0x8000
#define CANCEL_REG_IP (3-(union {int __i; char __b;}){1}.__b)

#elif defined(__i386__)
#define TP_ADJ(p) (p)
#define CANCEL_REG_IP 14

#elif defined(__x86_64__)
#define TP_ADJ(p) (p)
#define CANCEL_REG_IP 16

#else
#warning unsupported architecture
#endif