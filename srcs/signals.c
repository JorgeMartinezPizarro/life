/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 20:35:41 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/15 20:35:53 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"
#include <stdatomic.h>

/*
** SIGTERM/SIGINT are process-directed: the kernel can deliver them to
** any thread that hasn't blocked them, not just main, so this flag is
** genuinely written from a pool worker and read from the main loop.
** A plain volatile sig_atomic_t only promises safety for the classic
** single-threaded case (handler sets it, that same thread reads it
** later); it doesn't give the cross-thread visibility this needs, so
** this uses a C11 atomic instead. It also needs release/acquire, not
** relaxed ordering: relaxed only guarantees the access itself is
** atomic, not a happens-before edge between the write and the read,
** so a race detector has nothing to recognize as synchronized and
** (correctly, under relaxed) still flags it.
*/
static atomic_int	g_shutdown_requested = 0;

static void	request_shutdown(int sig)
{
	(void)sig;
	atomic_store_explicit(&g_shutdown_requested, 1, memory_order_release);
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, request_shutdown);
	signal(SIGTERM, request_shutdown);
}

int	shutdown_requested(void)
{
	return (atomic_load_explicit(&g_shutdown_requested, memory_order_acquire));
}
