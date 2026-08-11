import { redirect } from '@sveltejs/kit';
import { db } from '$lib/server/db';
import type { PageServerLoad } from './$types';

export const load: PageServerLoad = async ({ locals }) => {
	try {
		if (!locals.user) throw redirect(303, '/login');

		const user = await db.user.findUnique({
			where: { id: locals.user.id },
			include: {
				followers: {
					include: { following: true, }
				}
			}
		});

		if (!user) {
			throw redirect(303, '/login');
		}

		return { user };
	} catch (error) {
		console.error('Error loading profile:', error);
		throw redirect(303, '/login');
	}
};
