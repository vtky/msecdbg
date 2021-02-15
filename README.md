# msecdbg
!exploitable Crash Analyzer - MSEC Debugger Extensions

## Project Description
!exploitable (pronounced “bang exploitable”) is a Windows debugging extension (Windbg) that provides automated crash analysis and security risk assessment. The tool first creates hashes to determine the uniqueness of a crash and then assigns an exploitability rating to the crash: Exploitable, Probably Exploitable, Probably Not Exploitable, or Unknown. There is more detailed information about the tool in the following .pptx file or at http://www.microsoft.com/security/msec. Additonally, see the blog post at http://blogs.technet.com/srd/archive/2009/04/08/the-history-of-the-exploitable-crash-analyzer.aspx, or watch the video at http://channel9.msdn.com/posts/PDCNews/Bang-Exploitable-Security-Analyzer/.

This tool was created by the Microsoft Security Engineering Center (MSEC) Security Science Team. For more information on MSEC and the Security Science team, please visit http://www.microsoft.com/security/msec. To see what's being worked on presently, visit the Security Research and Development blog at http://blogs.technet.com/srd/.

New bits posted on 5/1/2013, changelog below:

1.6.0 Updates:

ARM Dump Support Added
Changed default hashing algorithm to SHA256
Added Support to chose the hashing algorithm used (for backwards compatibility)
Added support for custom exclude hash list
Updated -v output to show which frames are used to determine the major and minor hash
Added version number logging
Added line number and source file reporting
Added checking for exception handler chain corruption as an Exploitable case
Added Stack Exhaustion as a Probably Not Exploitable case
Added more AppVerifier symbols to the excluded symbols list
Added checking for kernel mode code running in user land as an Exploitable case
Moved "Read AV Near Null" to terminal rule status
Added "App Verifier Stop Detected"
Moved "Read AV Near Null" to Probably Not Exploitable
Moved "Write AV Near Null" to Unknown
Added the XLAT command for x86 and x64
Correctly pull the TEB32 for WOW process on 64 bit Windows
Translate stack exhaustion cases that manifest as Write AVs into stack exhaustion
Changed the naming of Stack Overflow to Stack Exhaustion
Fixed a bug in the logic determining if code is in user or kernel space

1.0.6 Updates:

External Release: June, 2009

1.0.5 Updates:

Updates to the excluded symbols list
Handle POP instructions that pop to memory
Handle PUSH instructions that push to memory
Treat POP instructions to memory the same as MOV instructions to memory

1.0.4 Updates:

Fixed a reporting and analysis bug, in which we change the faulting instruction as well as the invoking function when we skip excluded stack frames

1.0.3 Updates:

New state and gather functionality and analyze rules to identify exceptions where the faulting address is on the stack.
Hashes are fixed at 32 bit display (8 hex characters) and code locations are fixed at 64 bit display (16 hex characters).
Added support for the REP SCAS instruction in the disassembler
Fixed a serious bug in the wildcard match function, which would result in anything that matched up to the first wildcard matching the entire string
Fixed a bug in which the destination pointer registers were not being set to the tainted value set for Write AVs that required taint analysis
Fixed bugs in the distinction between source and data registers for taint tracking in some rep instructions

1.0.2 Updates:

When loading user mode mini-dumps, the Gather rule now correctly sets the stack context.

1.0.1 Updates:

A bug that resulted in overtainting H or L registers has been fixed.
Initial External Release: March, 2009
