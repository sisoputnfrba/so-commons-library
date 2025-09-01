/*
 * Copyright (C) 2025 Sistemas Operativos - UTN FRBA. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "crypto.h"

char *crypto_md5(void *source, size_t length) {
	unsigned char md_value[EVP_MAX_MD_SIZE];
	unsigned int md_len;

	EVP_MD_CTX *mdctx = EVP_MD_CTX_new();

	if (mdctx == NULL) {
		EVP_MD_CTX_free(mdctx);
		return NULL;
	}

	if (EVP_DigestInit_ex(mdctx, EVP_md5(), NULL) != 1) {
		EVP_MD_CTX_free(mdctx);
		return NULL;
	}

	if (EVP_DigestUpdate(mdctx, source, length) != 1) {
		EVP_MD_CTX_free(mdctx);
		return NULL;
	}

	if (EVP_DigestFinal_ex(mdctx, md_value, &md_len) != 1) {
		EVP_MD_CTX_free(mdctx);
		return NULL;
	}

	EVP_MD_CTX_free(mdctx);
	return mem_hexstring_plain(md_value, md_len);
}
