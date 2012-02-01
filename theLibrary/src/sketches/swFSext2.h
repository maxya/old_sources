#pragma once

//	Figure 1-1. floppy disk meta-data layout
//
//	offset   # of blocks description
//	-------- ----------- -----------
//		   0           1 boot record
//			 -- block group 0 --
//	(1024 bytes)       1 superblock
//		   2           1 group descriptors
//		   3           1 block bitmap
//		   4           1 inode bitmap
//		   5          23 inode table
//		  28        1412 data blocks
//  
//
//	Figure 1-2. 20mb partition meta-data layout
//
//	offset   # of blocks description
//	-------- ----------- -----------
//		   0           1 boot record
//			 -- block group 0 --
//	(1024 bytes)       1 superblock
//		   2           1 group descriptors
//		   3           1 block bitmap
//		   4           1 inode bitmap
//		   5         214 inode table
//		 219        7974 data blocks
//			 -- block group 1 --
//		8193           1 superblock backup
//		8194           1 group descriptors backup
//		8195           1 block bitmap
//		8196           1 inode bitmap
//		8197         214 inode table
//		8408        7974 data blocks
//			 -- block group 2 --
//	   16385           1 block bitmap
//	   16386           1 inode bitmap
//	   16387         214 inode table
//	   16601        3879 data blocks




//
//  Define EXT2_PREALLOCATE to preallocate data blocks for expanding files
//  
#define EXT2_PREALLOCATE
#define EXT2_DEFAULT_PREALLOC_BLOCKS	8

//
// The second extended file system version
//

#define EXT2FS_DATE		"95/08/09"
#define EXT2FS_VERSION		"0.5b"

//
// Special inode numbers
//
#define	EXT2_BAD_INO		 1	/* Bad blocks inode */
#define EXT2_ROOT_INO		 2	/* Root inode */
#define EXT2_ACL_IDX_INO	 3	/* ACL inode */
#define EXT2_ACL_DATA_INO	 4	/* ACL inode */
#define EXT2_BOOT_LOADER_INO	 5	/* Boot loader inode */
#define EXT2_UNDEL_DIR_INO	 6	/* Undelete directory inode */

// First non-reserved inode for old ext2 filesystems 
#define EXT2_GOOD_OLD_FIRST_INO	11

//
// The second extended file system magic number
//
#define EXT2_SUPER_MAGIC	0xEF53

//
// Maximal count of links to a file
//
#define EXT2_LINK_MAX		32000

//
// Macro-instructions used to manage several block sizes
//
#define EXT2_MIN_BLOCK_SIZE		1024
#define	EXT2_MAX_BLOCK_SIZE		4096
#define EXT2_MIN_BLOCK_LOG_SIZE		  10
#define EXT2_BLOCK_SIZE(s)		(EXT2_MIN_BLOCK_SIZE << (s)->s_log_block_size)
#define EXT2_ACLE_PER_BLOCK(s)		(EXT2_BLOCK_SIZE(s) / sizeof (struct EXT2_ACL_ENTRY))
#define	EXT2_ADDR_PER_BLOCK(s)		(EXT2_BLOCK_SIZE(s) / sizeof (UINT))
#define EXT2_BLOCK_SIZE_BITS(s)	((s)->s_log_block_size + 10)
#define EXT2_INODE_SIZE(s)	(((s)->s_rev_level == EXT2_GOOD_OLD_REV) ? \
				 EXT2_GOOD_OLD_INODE_SIZE : \
				 (s)->s_inode_size)
#define EXT2_FIRST_INO(s)	(((s)->s_rev_level == EXT2_GOOD_OLD_REV) ? \
				 EXT2_GOOD_OLD_FIRST_INO : \
				 (s)->s_first_ino)


//
// Macro-instructions used to manage fragments
//
#define EXT2_MIN_FRAG_SIZE		1024
#define	EXT2_MAX_FRAG_SIZE		4096
#define EXT2_MIN_FRAG_LOG_SIZE		  10
#define EXT2_FRAG_SIZE(s)		(EXT2_MIN_FRAG_SIZE << (s)->s_log_frag_size)
#define EXT2_FRAGS_PER_BLOCK(s)	(EXT2_BLOCK_SIZE(s) / EXT2_FRAG_SIZE(s))


//
// ACL structures
// 
struct EXT2_ACL_HEADER	/* Header of Access Control Lists */
{
	DWORD	aclh_size;
	DWORD	aclh_file_count;
	DWORD	aclh_acle_count;
	DWORD	aclh_first_acle;
};

struct EXT2_ACL_ENTRY	/* Access Control List Entry */
{
	DWORD	acle_size;
	WORD	acle_perms;	/* Access permissions */
	WORD	acle_type;	/* Type of entry */
	WORD	acle_tag;	/* User or group identity */
	WORD	acle_pad1;
	DWORD	acle_next;	/* Pointer on next entry for the */
					/* same inode or on next free entry */
};


//
// Structure of a blocks group descriptor
//
struct EXT2_GROUP_DESC
{
	DWORD	bg_block_bitmap;		/* Blocks bitmap block */
	DWORD	bg_inode_bitmap;		/* Inodes bitmap block */
	DWORD	bg_inode_table;		/* Inodes table block */
	WORD	bg_free_blocks_count;	/* Free blocks count */
	WORD	bg_free_inodes_count;	/* Free inodes count */
	WORD	bg_used_dirs_count;	/* Directories count */
	WORD	bg_pad;
	DWORD	bg_reserved[3];
};

//
// Macro-instructions used to manage group descriptors
// 
# define EXT2_BLOCKS_PER_GROUP(s)	((s)->s_blocks_per_group)
# define EXT2_DESC_PER_BLOCK(s)		(EXT2_BLOCK_SIZE(s) / sizeof (struct ext2_group_desc))
# define EXT2_INODES_PER_GROUP(s)	((s)->s_inodes_per_group)

//
// Constants relative to the data blocks
//
#define	EXT2_NDIR_BLOCKS		12
#define	EXT2_IND_BLOCK			EXT2_NDIR_BLOCKS
#define	EXT2_DIND_BLOCK			(EXT2_IND_BLOCK + 1)
#define	EXT2_TIND_BLOCK			(EXT2_DIND_BLOCK + 1)
#define	EXT2_N_BLOCKS			(EXT2_TIND_BLOCK + 1)

//
// Inode flags
//
#define	EXT2_SECRM_FL			0x00000001 /* Secure deletion */
#define	EXT2_UNRM_FL			0x00000002 /* Undelete */
#define	EXT2_COMPR_FL			0x00000004 /* Compress file */
#define EXT2_SYNC_FL			0x00000008 /* Synchronous updates */
#define EXT2_IMMUTABLE_FL		0x00000010 /* Immutable file */
#define EXT2_APPEND_FL			0x00000020 /* writes to file may only append */
#define EXT2_NODUMP_FL			0x00000040 /* do not dump file */
#define EXT2_NOATIME_FL			0x00000080 /* do not update atime */
// Reserved for compression usage... 
#define EXT2_DIRTY_FL			0x00000100
#define EXT2_COMPRBLK_FL		0x00000200 /* One or more compressed clusters */
#define EXT2_NOCOMP_FL			0x00000400 /* Don't compress */
#define EXT2_ECOMPR_FL			0x00000800 /* Compression error */
// End compression flags --- maybe not all used 
#define EXT2_BTREE_FL			0x00001000 /* btree format dir */
#define EXT2_RESERVED_FL		0x80000000 /* reserved for ext2 lib */

#define EXT2_FL_USER_VISIBLE		0x00001FFF /* User visible flags */
#define EXT2_FL_USER_MODIFIABLE		0x000000FF /* User modifiable flags */

/*
 * ioctl commands
 *
#define	EXT2_IOC_GETFLAGS		_IOR('f', 1, long)
#define	EXT2_IOC_SETFLAGS		_IOW('f', 2, long)
#define	EXT2_IOC_GETVERSION		_IOR('v', 1, long)
#define	EXT2_IOC_SETVERSION		_IOW('v', 2, long)
 */

//
// Structure of an inode on the disk
//
struct EXT2_INODE 
{
	WORD	i_mode;		/* File mode */
	WORD	i_uid;		/* Low 16 bits of Owner Uid */
	DWORD	i_size;		/* Size in bytes */
	DWORD	i_atime;	/* Access time */
	DWORD	i_ctime;	/* Creation time */
	DWORD	i_mtime;	/* Modification time */
	DWORD	i_dtime;	/* Deletion Time */
	WORD	i_gid;		/* Low 16 bits of Group Id */
	WORD	i_links_count;	/* Links count */
	DWORD	i_blocks;	/* Blocks count */
	DWORD	i_flags;	/* File flags */
	union {
		struct {
			DWORD  l_i_reserved1;
		} linux1;
		struct {
			DWORD  h_i_translator;
		} hurd1;
		struct {
			DWORD  m_i_reserved1;
		} masix1;
	} osd1;				/* OS dependent 1 */
	DWORD	i_block[EXT2_N_BLOCKS];/* Pointers to blocks */
	DWORD	i_generation;	/* File version (for NFS) */
	DWORD	i_file_acl;	/* File ACL */
	DWORD	i_dir_acl;	/* Directory ACL */
	DWORD	i_faddr;	/* Fragment address */
	union {
		struct {
			BYTE	l_i_frag;	/* Fragment number */
			BYTE	l_i_fsize;	/* Fragment size */
			WORD	i_pad1;
			WORD	l_i_uid_high;	/* these 2 fields    */
			WORD	l_i_gid_high;	/* were reserved2[0] */
			DWORD	l_i_reserved2;
		} linux2;
		struct {
			BYTE	h_i_frag;	/* Fragment number */
			BYTE	h_i_fsize;	/* Fragment size */
			WORD	h_i_mode_high;
			WORD	h_i_uid_high;
			WORD	h_i_gid_high;
			DWORD	h_i_author;
		} hurd2;
		struct {
			BYTE	m_i_frag;	/* Fragment number */
			BYTE	m_i_fsize;	/* Fragment size */
			WORD	m_pad1;
			DWORD	m_i_reserved2[2];
		} masix2;
	} osd2;				/* OS dependent 2 */
};

#define i_reserved1	osd1.linux1.l_i_reserved1
#define i_frag		osd2.linux2.l_i_frag
#define i_fsize		osd2.linux2.l_i_fsize
#define i_uid_low	i_uid
#define i_gid_low	i_gid
#define i_uid_high	osd2.linux2.l_i_uid_high
#define i_gid_high	osd2.linux2.l_i_gid_high
#define i_reserved2	osd2.linux2.l_i_reserved2

#define i_size_high	i_dir_acl

//
// File system states
//
#define	EXT2_VALID_FS			0x0001	/* Unmounted cleanly */
#define	EXT2_ERROR_FS			0x0002	/* Errors detected */

//
// Mount flags
//
#define EXT2_MOUNT_CHECK		0x0001	/* Do mount-time checks */
#define EXT2_MOUNT_GRPID		0x0004	/* Create files with directory's group */
#define EXT2_MOUNT_DEBUG		0x0008	/* Some debugging messages */
#define EXT2_MOUNT_ERRORS_CONT		0x0010	/* Continue on errors */
#define EXT2_MOUNT_ERRORS_RO		0x0020	/* Remount fs ro on errors */
#define EXT2_MOUNT_ERRORS_PANIC		0x0040	/* Panic on errors */
#define EXT2_MOUNT_MINIX_DF		0x0080	/* Mimics the Minix statfs */
#define EXT2_MOUNT_NO_UID32		0x0200  /* Disable 32-bit UIDs */

#define clear_opt(o, opt)		o &= ~EXT2_MOUNT_##opt
#define set_opt(o, opt)			o |= EXT2_MOUNT_##opt
#define test_opt(sb, opt)		((sb)->u.ext2_sb.s_mount_opt & \
					 EXT2_MOUNT_##opt)
//
// Maximal mount counts between two filesystem checks
//
#define EXT2_DFL_MAX_MNT_COUNT		20	/* Allow 20 mounts */
#define EXT2_DFL_CHECKINTERVAL		0	/* Don't use interval check */

//
// Behaviour when detecting errors
//
#define EXT2_ERRORS_CONTINUE		1	/* Continue execution */
#define EXT2_ERRORS_RO			2	/* Remount fs read-only */
#define EXT2_ERRORS_PANIC		3	/* Panic */
#define EXT2_ERRORS_DEFAULT		EXT2_ERRORS_CONTINUE

//
// Structure of the super block
//
struct EXT2_SUPER_BLOCK 
{
	DWORD	s_inodes_count;		/* Inodes count */
	DWORD	s_blocks_count;		/* Blocks count */
	DWORD	s_r_blocks_count;	/* Reserved blocks count */
	DWORD	s_free_blocks_count;	/* Free blocks count */
	DWORD	s_free_inodes_count;	/* Free inodes count */
	DWORD	s_first_data_block;	/* First Data Block */
	DWORD	s_log_block_size;	/* Block size */
	INT		s_log_frag_size;	/* Fragment size */
	DWORD	s_blocks_per_group;	/* # Blocks per group */
	DWORD	s_frags_per_group;	/* # Fragments per group */
	DWORD	s_inodes_per_group;	/* # Inodes per group */
	DWORD	s_mtime;		/* Mount time */
	DWORD	s_wtime;		/* Write time */
	WORD	s_mnt_count;		/* Mount count */
	SHORT	s_max_mnt_count;	/* Maximal mount count */
	WORD	s_magic;		/* Magic signature */
	WORD	s_state;		/* File system state */
	WORD	s_errors;		/* Behaviour when detecting errors */
	WORD	s_minor_rev_level; 	/* minor revision level */
	DWORD	s_lastcheck;		/* time of last check */
	DWORD	s_checkinterval;	/* max. time between checks */
	DWORD	s_creator_os;		/* OS */
	DWORD	s_rev_level;		/* Revision level */
	WORD	s_def_resuid;		/* Default uid for reserved blocks */
	WORD	s_def_resgid;		/* Default gid for reserved blocks */
	/*
	 * These fields are for EXT2_DYNAMIC_REV superblocks only.
	 *
	 * Note: the difference between the compatible feature set and
	 * the incompatible feature set is that if there is a bit set
	 * in the incompatible feature set that the kernel doesn't
	 * know about, it should refuse to mount the filesystem.
	 * 
	 * e2fsck's requirements are more strict; if it doesn't know
	 * about a feature in either the compatible or incompatible
	 * feature set, it must abort and not try to meddle with
	 * things it doesn't understand...
	 */
	DWORD	s_first_ino; 		/* First non-reserved inode */
	WORD	s_inode_size; 		/* size of inode structure */
	WORD	s_block_group_nr; 	/* block group # of this superblock */
	DWORD	s_feature_compat; 	/* compatible feature set */
	DWORD	s_feature_incompat; 	/* incompatible feature set */
	DWORD	s_feature_ro_compat; 	/* readonly-compatible feature set */
	BYTE	s_uuid[16];		/* 128-bit uuid for volume */
	char	s_volume_name[16]; 	/* volume name */
	char	s_last_mounted[64]; 	/* directory where last mounted */
	DWORD	s_algorithm_usage_bitmap; /* For compression */
	/*
	 * Performance hints.  Directory preallocation should only
	 * happen if the EXT2_COMPAT_PREALLOC flag is on.
	 */
	BYTE	s_prealloc_blocks;	/* Nr of blocks to try to preallocate*/
	BYTE	s_prealloc_dir_blocks;	/* Nr to preallocate for dirs */
	WORD	s_padding1;
	DWORD	s_reserved[204];	/* Padding to the end of the block */
};

// Assume that user mode programs are passing in an ext2fs superblock, not
// a kernel struct super_block.  This will allow us to call the feature-test
// macros from user land. 
#define EXT2_SB(sb)	(sb)

//
// Codes for operating systems
//
#define EXT2_OS_LINUX		0
#define EXT2_OS_HURD		1
#define EXT2_OS_MASIX		2
#define EXT2_OS_FREEBSD		3
#define EXT2_OS_LITES		4

//
// Revision levels
//
#define EXT2_GOOD_OLD_REV	0	/* The good old (original) format */
#define EXT2_DYNAMIC_REV	1 	/* V2 format w/ dynamic inode sizes */

#define EXT2_CURRENT_REV	EXT2_GOOD_OLD_REV
#define EXT2_MAX_SUPP_REV	EXT2_DYNAMIC_REV

#define EXT2_GOOD_OLD_INODE_SIZE 128

//
// Feature set definitions
//

#define EXT2_HAS_COMPAT_FEATURE(sb,mask)			\
	( EXT2_SB(sb)->s_es->s_feature_compat & cpu_to_le32(mask) )
#define EXT2_HAS_RO_COMPAT_FEATURE(sb,mask)			\
	( EXT2_SB(sb)->s_es->s_feature_ro_compat & cpu_to_le32(mask) )
#define EXT2_HAS_INCOMPAT_FEATURE(sb,mask)			\
	( EXT2_SB(sb)->s_es->s_feature_incompat & cpu_to_le32(mask) )
#define EXT2_SET_COMPAT_FEATURE(sb,mask)			\
	EXT2_SB(sb)->s_es->s_feature_compat |= cpu_to_le32(mask)
#define EXT2_SET_RO_COMPAT_FEATURE(sb,mask)			\
	EXT2_SB(sb)->s_es->s_feature_ro_compat |= cpu_to_le32(mask)
#define EXT2_SET_INCOMPAT_FEATURE(sb,mask)			\
	EXT2_SB(sb)->s_es->s_feature_incompat |= cpu_to_le32(mask)
#define EXT2_CLEAR_COMPAT_FEATURE(sb,mask)			\
	EXT2_SB(sb)->s_es->s_feature_compat &= ~cpu_to_le32(mask)
#define EXT2_CLEAR_RO_COMPAT_FEATURE(sb,mask)			\
	EXT2_SB(sb)->s_es->s_feature_ro_compat &= ~cpu_to_le32(mask)
#define EXT2_CLEAR_INCOMPAT_FEATURE(sb,mask)			\
	EXT2_SB(sb)->s_es->s_feature_incompat &= ~cpu_to_le32(mask)

#define EXT2_FEATURE_COMPAT_DIR_PREALLOC	0x0001
#define EXT2_FEATURE_COMPAT_IMAGIC_INODES	0x0002
#define EXT3_FEATURE_COMPAT_HAS_JOURNAL		0x0004
#define EXT2_FEATURE_COMPAT_EXT_ATTR		0x0008
#define EXT2_FEATURE_COMPAT_RESIZE_INO		0x0010
#define EXT2_FEATURE_COMPAT_DIR_INDEX		0x0020
#define EXT2_FEATURE_COMPAT_ANY			0xffffffff

#define EXT2_FEATURE_RO_COMPAT_SPARSE_SUPER	0x0001
#define EXT2_FEATURE_RO_COMPAT_LARGE_FILE	0x0002
#define EXT2_FEATURE_RO_COMPAT_BTREE_DIR	0x0004
#define EXT2_FEATURE_RO_COMPAT_ANY		0xffffffff

#define EXT2_FEATURE_INCOMPAT_COMPRESSION	0x0001
#define EXT2_FEATURE_INCOMPAT_FILETYPE		0x0002
#define EXT3_FEATURE_INCOMPAT_RECOVER		0x0004
#define EXT3_FEATURE_INCOMPAT_JOURNAL_DEV	0x0008
#define EXT2_FEATURE_INCOMPAT_ANY		0xffffffff

#define EXT2_FEATURE_COMPAT_SUPP	0
#define EXT2_FEATURE_INCOMPAT_SUPP	EXT2_FEATURE_INCOMPAT_FILETYPE
#define EXT2_FEATURE_RO_COMPAT_SUPP	(EXT2_FEATURE_RO_COMPAT_SPARSE_SUPER| \
					 EXT2_FEATURE_RO_COMPAT_LARGE_FILE| \
					 EXT2_FEATURE_RO_COMPAT_BTREE_DIR)
#define EXT2_FEATURE_RO_COMPAT_UNSUPPORTED	~EXT2_FEATURE_RO_COMPAT_SUPP
#define EXT2_FEATURE_INCOMPAT_UNSUPPORTED	~EXT2_FEATURE_INCOMPAT_SUPP


//
// Default values for user and/or group using reserved blocks
// 
#define	EXT2_DEF_RESUID		0
#define	EXT2_DEF_RESGID		0

//
// Structure of a directory entry
//
#define EXT2_NAME_LEN 255

struct EXT2_DIR_ENTRY {
	DWORD	inode;			/* Inode number */
	WORD	rec_len;		/* Directory entry length */
	WORD	name_len;		/* Name length */
	char	name[EXT2_NAME_LEN];	/* File name */
};

/*
 * The new version of the directory entry.  Since EXT2 structures are
 * stored in intel byte order, and the name_len field could never be
 * bigger than 255 chars, it's safe to reclaim the extra byte for the
 * file_type field.
 */
struct EXT2_DIR_ENTRY2 {
	DWORD	inode;			/* Inode number */
	WORD	rec_len;		/* Directory entry length */
	BYTE	name_len;		/* Name length */
	BYTE	file_type;
	char	name[EXT2_NAME_LEN];	/* File name */
};

/*
 * Ext2 directory file types.  Only the low 3 bits are used.  The
 * other bits are reserved for now.
 */
enum {
	EXT2_FT_UNKNOWN,
	EXT2_FT_REG_FILE,
	EXT2_FT_DIR,
	EXT2_FT_CHRDEV,
	EXT2_FT_BLKDEV,
	EXT2_FT_FIFO,
	EXT2_FT_SOCK,
	EXT2_FT_SYMLINK,
	EXT2_FT_MAX
};

/*
 * EXT2_DIR_PAD defines the directory entries boundaries
 *
 * NOTE: It must be a multiple of 4
 */
#define EXT2_DIR_PAD		 	4
#define EXT2_DIR_ROUND 			(EXT2_DIR_PAD - 1)
#define EXT2_DIR_REC_LEN(name_len)	(((name_len) + 8 + EXT2_DIR_ROUND) & \
					 ~EXT2_DIR_ROUND)
//
//
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ THE END ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//
//
//
#if 0
/*
 * Function prototypes
 */

/*
 * Ok, these declarations are also in <linux/kernel.h> but none of the
 * ext2 source programs needs to include it so they are duplicated here.
 */
# define NORET_TYPE    /**/
# define ATTRIB_NORET  __attribute__((noreturn))
# define NORET_AND     noreturn,

/* acl.c */
extern int ext2_permission (struct inode *, int);

/* balloc.c */
extern int ext2_bg_has_super(struct super_block *sb, int group);
extern unsigned long ext2_bg_num_gdb(struct super_block *sb, int group);
extern int ext2_new_block (struct inode *, unsigned long,
			   DWORD *, DWORD *, int *);
extern void ext2_free_blocks (struct inode *, unsigned long,
			      unsigned long);
extern unsigned long ext2_count_free_blocks (struct super_block *);
extern void ext2_check_blocks_bitmap (struct super_block *);
extern struct ext2_group_desc * ext2_get_group_desc(struct super_block * sb,
						    unsigned int block_group,
						    struct buffer_head ** bh);

/* bitmap.c */
extern unsigned long ext2_count_free (struct buffer_head *, unsigned);

/* dir.c */

/* file.c */
extern int ext2_read (struct inode *, struct file *, char *, int);
extern int ext2_write (struct inode *, struct file *, char *, int);

/* fsync.c */
extern int ext2_sync_file (struct file *, struct dentry *, int);
extern int ext2_fsync_inode (struct inode *, int);

/* ialloc.c */
extern struct inode * ext2_new_inode (const struct inode *, int);
extern void ext2_free_inode (struct inode *);
extern unsigned long ext2_count_free_inodes (struct super_block *);
extern void ext2_check_inodes_bitmap (struct super_block *);

/* inode.c */

extern struct buffer_head * ext2_getblk (struct inode *, long, int, int *);
extern struct buffer_head * ext2_bread (struct inode *, int, int, int *);

extern void ext2_read_inode (struct inode *);
extern void ext2_write_inode (struct inode *, int);
extern void ext2_put_inode (struct inode *);
extern void ext2_delete_inode (struct inode *);
extern int ext2_sync_inode (struct inode *);
extern void ext2_discard_prealloc (struct inode *);

/* ioctl.c */
extern int ext2_ioctl (struct inode *, struct file *, unsigned int,
		       unsigned long);

/* namei.c */
extern struct inode_operations ext2_dir_inode_operations;

/* super.c */
extern void ext2_error (struct super_block *, const char *, const char *, ...)
	__attribute__ ((format (printf, 3, 4)));
extern NORET_TYPE void ext2_panic (struct super_block *, const char *,
				   const char *, ...)
	__attribute__ ((NORET_AND format (printf, 3, 4)));
extern void ext2_warning (struct super_block *, const char *, const char *, ...)
	__attribute__ ((format (printf, 3, 4)));
extern void ext2_update_dynamic_rev (struct super_block *sb);
extern void ext2_put_super (struct super_block *);
extern void ext2_write_super (struct super_block *);
extern int ext2_remount (struct super_block *, int *, char *);
extern struct super_block * ext2_read_super (struct super_block *,void *,int);
extern int ext2_statfs (struct super_block *, struct statfs *);

/* truncate.c */
extern void ext2_truncate (struct inode *);

/*
 * Inodes and files operations
 */

/* dir.c */
extern struct file_operations ext2_dir_operations;
extern int ext2_add_link (struct dentry *, struct inode *);
extern ino_t ext2_inode_by_name(struct inode *, struct dentry *);
extern int ext2_make_empty(struct inode *, struct inode *);
extern struct ext2_dir_entry_2 * ext2_find_entry (struct inode *,struct dentry *, struct page **);
extern int ext2_delete_entry (struct ext2_dir_entry_2 *, struct page *);
extern int ext2_empty_dir (struct inode *);
extern struct ext2_dir_entry_2 * ext2_dotdot (struct inode *, struct page **);
extern void ext2_set_link(struct inode *, struct ext2_dir_entry_2 *, struct page *, struct inode *);

/* file.c */
extern struct inode_operations ext2_file_inode_operations;
extern struct file_operations ext2_file_operations;

/* symlink.c */
extern struct inode_operations ext2_fast_symlink_inode_operations;

extern struct address_space_operations ext2_aops;

#endif	/* 0 */

#endif	/* _LINUX_EXT2_FS_H */
