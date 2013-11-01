/*====================================================================*
 -  Copyright (C) 2001 Leptonica.  All rights reserved.
 -  This software is distributed in the hope that it will be
 -  useful, but with NO WARRANTY OF ANY KIND.
 -  No author or distributor accepts responsibility to anyone for the
 -  consequences of using this software, or for whether it serves any
 -  particular purpose or works at all, unless he or she says so in
 -  writing.  Everyone is granted permission to copy, modify and
 -  redistribute this source code, for commercial or non-commercial
 -  purposes, with the following restrictions: (1) the origin of this
 -  source code must not be misrepresented; (2) modified versions must
 -  be plainly marked as such; and (3) this notice may not be removed
 -  or altered from any source or modified source distribution.
 *====================================================================*/

/*
 * correlscore.c
 *
 *     These are functions for computing correlation between
 *     pairs of 1 bpp images.
 *
 *         l_float32   pixCorrelationScore()
 *         l_int32     pixCorrelationScoreThresholded()
 *         l_float32   pixCorrelationScoreSimple()
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "allheaders.h"


/*!
 *  pixCorrelationScore()
 *
 *      Input:  pix1   (test pix, 1 bpp)
 *              pix2   (exemplar pix, 1 bpp)
 *              area1  (number of on pixels in pix1)
 *              area2  (number of on pixels in pix2)
 *              delx   (x comp of centroid difference)
 *              dely   (y comp of centroid difference)
 *              maxdiffw (max width difference of pix1 and pix2)
 *              maxdiffh (max height difference of pix1 and pix2)
 *              tab    (sum tab for byte)
 *      Return: correlation score 
 *
 *  Note: we check first that the two pix are roughly the same size.
 *  For jbclass (jbig2) applications at roughly 300 ppi, maxdiffw and
 *  maxdiffh should be at least 2.
 *
 *  Only if they meet that criterion do we compare the bitmaps. 
 *  The centroid difference is used to align the two images to the
 *  nearest integer for the correlation.
 *
 *  The correlation score is the ratio of the square of the number of
 *  pixels in the AND of the two bitmaps to the product of the number
 *  of ON pixels in each.  Denote the number of ON pixels in pix1
 *  by |1|, the number in pix2 by |2|, and the number in the AND
 *  of pix1 and pix2 by |1 & 2|.  The correlation score is then
 *  (|1 & 2|)**2 / (|1|*|2|).
 *
 *  This score is compared with an input threshold, which can
 *  be modified depending on the weight of the template.
 *  The modified threshold is
 *     thresh + (1.0 - thresh) * weight * R
 *  where 
 *     weight is a fixed input factor between 0.0 and 1.0
 *     R = |2| / area(2)
 *  and area(2) is the total number of pixels in 2 (i.e., width x height).
 *
 *  To understand why a weight factor is useful, consider what happens
 *  with thick, sans-serif characters that look similar and have a value
 *  of R near 1.  Different characters can have a high correlation value,
 *  and the classifier will make incorrect substitutions.  The weight
 *  factor raises the threshold for these characters.
 *
 *  Yet another approach to reduce such substitutions is to run the classifier
 *  in a non-greedy way, matching to the template with the highest
 *  score, not the first template with a score satisfying the matching
 *  constraint.  However, this is not particularly effective.
 *
 *  The implementation here gives the same result as in
 *  pixCorrelationScoreSimple(), where a temporary Pix is made to hold
 *  the AND and implementation uses rasterop:
 *      pixt = pixCreateTemplate(pix1);
 *      pixRasterop(pixt, idelx, idely, wt, ht, PIX_SRC, pix2, 0, 0);
 *      pixRasterop(pixt, 0, 0, wi, hi, PIX_SRC & PIX_DST, pix1, 0, 0);
 *      pixCountPixels(pixt, &count, tab);
 *      pixDestroy(&pixt);
 *  However, here it is done in a streaming fashion, counting as it goes,
 *  and touching memory exactly once, giving a 3-4x speedup over the
 *  simple implementation.  This very fast correlation matcher was
 *  contributed by William Rucklidge.
 */
l_float32
pixCorrelationScore(PIX       *pix1,
                    PIX       *pix2,
                    l_int32    area1,
                    l_int32    area2,
                    l_float32  delx,   /* x(1) - x(3) */
                    l_float32  dely,   /* y(1) - y(3) */
                    l_int32    maxdiffw,
                    l_int32    maxdiffh,
                    l_int32   *tab)
{
l_int32    wi, hi, wt, ht, delw, delh, idelx, idely, count;
l_int32    wpl1, wpl2, lorow, hirow, locol, hicol;
l_int32    x, y, pix1lskip, pix2lskip, rowwords1, rowwords2;
l_uint32   word1, word2, andw;
l_uint32  *row1, *row2;
l_float32  score;

    PROCNAME("pixCorrelationScore");

    if (!pix1 || pixGetDepth(pix1) != 1)
        return (l_float32)ERROR_FLOAT("pix1 not 1 bpp", procName, 0.0);
    if (!pix2 || pixGetDepth(pix2) != 1)
        return (l_float32)ERROR_FLOAT("pix2 not 1 bpp", procName, 0.0);
    if (!tab)
        return (l_float32)ERROR_FLOAT("tab not defined", procName, 0.0);
    if (area1 <= 0 || area2 <= 0)
        return (l_float32)ERROR_FLOAT("areas must be > 0", procName, 0.0);

        /* Eliminate based on size difference */
    pixGetDimensions(pix1, &wi, &hi, NULL);
    pixGetDimensions(pix2, &wt, &ht, NULL);
    delw = L_ABS(wi - wt);
    if (delw > maxdiffw)
        return 0.0;
    delh = L_ABS(hi - ht);
    if (delh > maxdiffh)
        return 0.0;

        /* Round difference to nearest integer */
    if (delx >= 0)
        idelx = (l_int32)(delx + 0.5);
    else
        idelx = (l_int32)(delx - 0.5);
    if (dely >= 0)
        idely = (l_int32)(dely + 0.5);
    else
        idely = (l_int32)(dely - 0.5);

    count = 0;
    wpl1 = pixGetWpl(pix1);
    wpl2 = pixGetWpl(pix2);
    rowwords2 = wpl2;

        /* What rows of pix1 need to be considered?  Only those underlying the
         * shifted pix2. */
    lorow = L_MAX(idely, 0);
    hirow = L_MIN(ht + idely, hi);

        /* Get the pointer to the first row of each image that will be
         * considered. */
    row1 = pixGetData(pix1) + wpl1 * lorow;
    row2 = pixGetData(pix2) + wpl2 * (lorow - idely);

        /* Similarly, figure out which columns of pix1 will be considered. */
    locol = L_MAX(idelx, 0);
    hicol = L_MIN(wt + idelx, wi);

    if (idelx >= 32) {
            /* pix2 is shifted far enough to the right that pix1's first
             * word(s) won't contribute to the count.  Increment its
             * pointer to point to the first word that will contribute,
             * and adjust other values accordingly. */
        pix1lskip = idelx >> 5;  /* # of words to skip on left */
        row1 += pix1lskip;
        locol -= pix1lskip << 5;
        hicol -= pix1lskip << 5;
        idelx &= 31;
    } else if (idelx <= -32) {
            /* pix2 is shifted far enough to the left that its first word(s)
             * won't contribute to the count.  Increment its pointer
             * to point to the first word that will contribute,
             * and adjust other values accordingly. */
        pix2lskip = -((idelx + 31) >> 5);  /* # of words to skip on left */
        row2 += pix2lskip;
        rowwords2 -= pix2lskip;
        idelx += pix2lskip << 5;
    }

    if ((locol >= hicol) || (lorow >= hirow)) {  /* there is no overlap */
        count = 0;
    } else {
            /* How many words of each row of pix1 need to be considered? */
        rowwords1 = (hicol + 31) >> 5;

        if (idelx == 0) {
                /* There's no lateral offset; simple case. */
            for (y = lorow; y < hirow; y++, row1 += wpl1, row2 += wpl2) {
                for (x = 0; x < rowwords1; x++) {
                    andw = row1[x] & row2[x];
                    count += tab[andw & 0xff] +
                        tab[(andw >> 8) & 0xff] +
                        tab[(andw >> 16) & 0xff] +
                        tab[andw >> 24];
                }
            }
        } else if (idelx > 0) {
                /* pix2 is shifted to the right.  word 0 of pix1 is touched by
                 * word 0 of pix2; word 1 of pix1 is touched by word 0 and word
                 * 1 of pix2, and so on up to the last word of pix1 (word N),
                 * which is touched by words N-1 and N of pix1... if there is a
                 * word N.  Handle the two cases (pix2 has N-1 words and pix2
                 * has at least N words) separately.
                 *
                 * Note: we know that pix2 has at least N-1 words (i.e.,
                 * rowwords2 >= rowwords1 - 1) by the following logic.
                 * We can pretend that idelx <= 31 because the >= 32 logic
                 * above adjusted everything appropriately.  Then
                 * hicol <= wt + idelx <= wt + 31, so
                 * hicol + 31 <= wt + 62
                 * rowwords1 = (hicol + 31) >> 5 <= (wt + 62) >> 5
                 * rowwords2 == (wt + 31) >> 5, so
                 * rowwords1 <= rowwords2 + 1 */
            if (rowwords2 < rowwords1) {
                for (y = lorow; y < hirow; y++, row1 += wpl1, row2 += wpl2) {
                        /* Do the first iteration so the loop can be
                         * branch-free. */
                    word1 = row1[0];
                    word2 = row2[0] >> idelx;
                    andw = word1 & word2;
                    count += tab[andw & 0xff] +
                        tab[(andw >> 8) & 0xff] +
                        tab[(andw >> 16) & 0xff] +
                        tab[andw >> 24];

                    for (x = 1; x < rowwords2; x++) {
                        word1 = row1[x];
                        word2 = (row2[x] >> idelx) |
                            (row2[x - 1] << (32 - idelx));
                        andw = word1 & word2;
                        count += tab[andw & 0xff] +
                            tab[(andw >> 8) & 0xff] +
                            tab[(andw >> 16) & 0xff] +
                            tab[andw >> 24];
                    }

                        /* Now the last iteration - we know that this is safe
                         * (i.e.  rowwords1 >= 2) because rowwords1 > rowwords2
                         * > 0 (if it was 0, we'd have taken the "count = 0"
                         * fast-path out of here). */
                    word1 = row1[x];
                    word2 = row2[x - 1] << (32 - idelx);
                    andw = word1 & word2;
                    count += tab[andw & 0xff] +
                        tab[(andw >> 8) & 0xff] +
                        tab[(andw >> 16) & 0xff] +
                        tab[andw >> 24];
                }
            } else {
                for (y = lorow; y < hirow; y++, row1 += wpl1, row2 += wpl2) {
                        /* Do the first iteration so the loop can be
                         * branch-free.  This section is the same as above
                         * except for the different limit on the loop, since
                         * the last iteration is the same as all the other
                         * iterations (beyond the first). */
                    word1 = row1[0];
                    word2 = row2[0] >> idelx;
                    andw = word1 & word2;
                    count += tab[andw & 0xff] +
                        tab[(andw >> 8) & 0xff] +
                        tab[(andw >> 16) & 0xff] +
                        tab[andw >> 24];

                    for (x = 1; x < rowwords1; x++) {
                        word1 = row1[x];
                        word2 = (row2[x] >> idelx) |
                            (row2[x - 1] << (32 - idelx));
                        andw = word1 & word2;
                        count += tab[andw & 0xff] +
                            tab[(andw >> 8) & 0xff] +
                            tab[(andw >> 16) & 0xff] +
                            tab[andw >> 24];
                    }
                }
            }
        } else {
                /* pix2 is shifted to the left.  word 0 of pix1 is touched by
                 * word 0 and word 1 of pix2, and so on up to the last word of
                 * pix1 (word N), which is touched by words N and N+1 of
                 * pix2... if there is a word N+1.  Handle the two cases (pix2
                 * has N words and pix2 has at least N+1 words) separately. */
            if (rowwords1 < rowwords2) {
                    /* pix2 has at least N+1 words, so every iteration through
                     * the loop can be the same. */
                for (y = lorow; y < hirow; y++, row1 += wpl1, row2 += wpl2) {
                    for (x = 0; x < rowwords1; x++) {
                        word1 = row1[x];
                        word2 = row2[x] << -idelx;
                        word2 |= row2[x + 1] >> (32 + idelx);
                        andw = word1 & word2;
                        count += tab[andw & 0xff] +
                            tab[(andw >> 8) & 0xff] +
                            tab[(andw >> 16) & 0xff] +
                            tab[andw >> 24];
                    }
                }
            } else {
                    /* pix2 has only N words, so the last iteration is broken
                     * out. */
                for (y = lorow; y < hirow; y++, row1 += wpl1, row2 += wpl2) {
                    for (x = 0; x < rowwords1 - 1; x++) {
                        word1 = row1[x];
                        word2 = row2[x] << -idelx;
                        word2 |= row2[x + 1] >> (32 + idelx);
                        andw = word1 & word2;
                        count += tab[andw & 0xff] +
                            tab[(andw >> 8) & 0xff] +
                            tab[(andw >> 16) & 0xff] +
                            tab[andw >> 24];
                    }

                    word1 = row1[x];
                    word2 = row2[x] << -idelx;
                    andw = word1 & word2;
                    count += tab[andw & 0xff] +
                        tab[(andw >> 8) & 0xff] +
                        tab[(andw >> 16) & 0xff] +
                        tab[andw >> 24];
                }
            }
        }
    }

    score = (l_float32)(count * count) / (l_float32)(area1 * area2);
/*    fprintf(stderr, "score = %7.3f, count = %d, area1 = %d, area2 = %d\n",
             score, count, area1, area2); */
    return score;
}


/*!
 *  pixCorrelationScoreThresholded()
 *
 *      Input:  pix1   (test pix, 1 bpp)
 *              pix2   (exemplar pix, 1 bpp)
 *              area1  (number of on pixels in pix1)
 *              area2  (number of on pixels in pix2)
 *              delx   (x comp of centroid difference)
 *              dely   (y comp of centroid difference)
 *              maxdiffw (max width difference of pix1 and pix2)
 *              maxdiffh (max height difference of pix1 and pix2)
 *              tab    (sum tab for byte)
 *              downcount (count of 1 pixels below each row of pix1)
 *              score_threshold
 *      Return: whether the correlation score is >= score_threshold
 *
 *
 *  Note: we check first that the two pix are roughly the same size.
 *  Only if they meet that criterion do we compare the bitmaps.
 *  The centroid difference is used to align the two images to the
 *  nearest integer for the correlation.
 *
 *  The correlation score is the ratio of the square of the number of
 *  pixels in the AND of the two bitmaps to the product of the number
 *  of ON pixels in each.  Denote the number of ON pixels in pix1
 *  by |1|, the number in pix2 by |2|, and the number in the AND
 *  of pix1 and pix2 by |1 & 2|.  The correlation score is then
 *  (|1 & 2|)**2 / (|1|*|2|).
 *
 *  This score is compared with an input threshold, which can
 *  be modified depending on the weight of the template.
 *  The modified threshold is
 *     thresh + (1.0 - thresh) * weight * R
 *  where
 *     weight is a fixed input factor between 0.0 and 1.0
 *     R = |2| / area(2)
 *  and area(2) is the total number of pixels in 2 (i.e., width x height).
 *
 *  To understand why a weight factor is useful, consider what happens
 *  with thick, sans-serif characters that look similar and have a value
 *  of R near 1.  Different characters can have a high correlation value,
 *  and the classifier will make incorrect substitutions.  The weight
 *  factor raises the threshold for these characters.
 *
 *  Yet another approach to reduce such substitutions is to run the classifier
 *  in a non-greedy way, matching to the template with the highest
 *  score, not the first template with a score satisfying the matching
 *  constraint.  However, this is not particularly effective.
 *
 *  This very fast correlation matcher was contributed by William Rucklidge.
 */
l_int32
pixCorrelationScoreThresholded(PIX       *pix1,
                               PIX       *pix2,
                               l_int32    area1,
                               l_int32    area2,
                               l_float32  delx,   /* x(1) - x(3) */
                               l_float32  dely,   /* y(1) - y(3) */
                               l_int32    maxdiffw,
                               l_int32    maxdiffh,
                               l_int32   *tab,
                               l_int32   *downcount,
                               l_float32  score_threshold)
{
l_int32    wi, hi, wt, ht, delw, delh, idelx, idely, count;
l_int32    wpl1, wpl2, lorow, hirow, locol, hicol, untouchable;
l_int32    x, y, pix1lskip, pix2lskip, rowwords1, rowwords2;
l_uint32   word1, word2, andw;
l_uint32  *row1, *row2;
l_float32  score;
l_int32    threshold;

    PROCNAME("pixCorrelationScoreThresholded");

    if (!pix1 || pixGetDepth(pix1) != 1)
        return ERROR_INT("pix1 not 1 bpp", procName, 0);
    if (!pix2 || pixGetDepth(pix2) != 1)
        return ERROR_INT("pix2 not 1 bpp", procName, 0);
    if (!tab)
        return ERROR_INT("tab not defined", procName, 0);
    if (area1 <= 0 || area2 <= 0)
        return ERROR_INT("areas must be > 0", procName, 0);

        /* Eliminate based on size difference */
    pixGetDimensions(pix1, &wi, &hi, NULL);
    pixGetDimensions(pix2, &wt, &ht, NULL);
    delw = L_ABS(wi - wt);
    if (delw > maxdiffw)
        return FALSE;
    delh = L_ABS(hi - ht);
    if (delh > maxdiffh)
        return FALSE;

        /* Round difference to nearest integer */
    if (delx >= 0)
        idelx = (l_int32)(delx + 0.5);
    else
        idelx = (l_int32)(delx - 0.5);
    if (dely >= 0)
        idely = (l_int32)(dely + 0.5);
    else
        idely = (l_int32)(dely - 0.5);

        /* Compute the correlation count that is needed so that
         * count * count / (area1 * area2) >= score_threshold */
    threshold = (l_int32)ceil(sqrt(score_threshold * area1 * area2));

    count = 0;
    wpl1 = pixGetWpl(pix1);
    wpl2 = pixGetWpl(pix2);
    rowwords2 = wpl2;

        /* What rows of pix1 need to be considered?  Only those underlying the
         * shifted pix2. */
    lorow = L_MAX(idely, 0);
    hirow = L_MIN(ht + idely, hi);

        /* Get the pointer to the first row of each image that will be
         * considered. */
    row1 = pixGetData(pix1) + wpl1 * lorow;
    row2 = pixGetData(pix2) + wpl2 * (lorow - idely);
    if (hirow <= hi) {
            /* Some rows of pix1 will never contribute to count */
        untouchable = downcount[hirow - 1];
    }

        /* Similarly, figure out which columns of pix1 will be considered. */
    locol = L_MAX(idelx, 0);
    hicol = L_MIN(wt + idelx, wi);

    if (idelx >= 32) {
            /* pix2 is shifted far enough to the right that pix1's first
             * word(s) won't contribute to the count.  Increment its
             * pointer to point to the first word that will contribute,
             * and adjust other values accordingly. */
        pix1lskip = idelx >> 5;  /* # of words to skip on left */
        row1 += pix1lskip;
        locol -= pix1lskip << 5;
        hicol -= pix1lskip << 5;
        idelx &= 31;
    } else if (idelx <= -32) {
            /* pix2 is shifted far enough to the left that its first word(s)
             * won't contribute to the count.  Increment its pointer
             * to point to the first word that will contribute,
             * and adjust other values accordingly. */
        pix2lskip = -((idelx + 31) >> 5);  /* # of words to skip on left */
        row2 += pix2lskip;
        rowwords2 -= pix2lskip;
        idelx += pix2lskip << 5;
    }

    if ((locol >= hicol) || (lorow >= hirow)) {  /* there is no overlap */
        count = 0;
    } else {
            /* How many words of each row of pix1 need to be considered? */
        rowwords1 = (hicol + 31) >> 5;

        if (idelx == 0) {
                /* There's no lateral offset; simple case. */
            for (y = lorow; y < hirow; y++, row1 += wpl1, row2 += wpl2) {
                for (x = 0; x < rowwords1; x++) {
                    andw = row1[x] & row2[x];
                    count += tab[andw & 0xff] +
                        tab[(andw >> 8) & 0xff] +
                        tab[(andw >> 16) & 0xff] +
                        tab[andw >> 24];
                }

                    /* If the count is over the threshold, no need to
                     * calculate any futher.  Likewise, return early if the
                     * count plus the maximum count attainable from further
                     * rows is below the threshold. */
                if (count >= threshold) return TRUE;
                if (count + downcount[y] - untouchable < threshold) {
                    return FALSE;
                }
            }
        } else if (idelx > 0) {
                /* pix2 is shifted to the right.  word 0 of pix1 is touched by
                 * word 0 of pix2; word 1 of pix1 is touched by word 0 and word
                 * 1 of pix2, and so on up to the last word of pix1 (word N),
                 * which is touched by words N-1 and N of pix1... if there is a
                 * word N.  Handle the two cases (pix2 has N-1 words and pix2
                 * has at least N words) separately.
                 *
                 * Note: we know that pix2 has at least N-1 words (i.e.,
                 * rowwords2 >= rowwords1 - 1) by the following logic.
                 * We can pretend that idelx <= 31 because the >= 32 logic
                 * above adjusted everything appropriately.  Then
                 * hicol <= wt + idelx <= wt + 31, so
                 * hicol + 31 <= wt + 62
                 * rowwords1 = (hicol + 31) >> 5 <= (wt + 62) >> 5
                 * rowwords2 == (wt + 31) >> 5, so
                 * rowwords1 <= rowwords2 + 1 */
            if (rowwords2 < rowwords1) {
                for (y = lorow; y < hirow; y++, row1 += wpl1, row2 += wpl2) {
                        /* Do the first iteration so the loop can be
                         * branch-free. */
                    word1 = row1[0];
                    word2 = row2[0] >> idelx;
                    andw = word1 & word2;
                    count += tab[andw & 0xff] +
                        tab[(andw >> 8) & 0xff] +
                        tab[(andw >> 16) & 0xff] +
                        tab[andw >> 24];

                    for (x = 1; x < rowwords2; x++) {
                        word1 = row1[x];
                        word2 = (row2[x] >> idelx) |
                            (row2[x - 1] << (32 - idelx));
                        andw = word1 & word2;
                        count += tab[andw & 0xff] +
                            tab[(andw >> 8) & 0xff] +
                            tab[(andw >> 16) & 0xff] +
                            tab[andw >> 24];
                    }

                        /* Now the last iteration - we know that this is safe
                         * (i.e.  rowwords1 >= 2) because rowwords1 > rowwords2
                         * > 0 (if it was 0, we'd have taken the "count = 0"
                         * fast-path out of here). */
                    word1 = row1[x];
                    word2 = row2[x - 1] << (32 - idelx);
                    andw = word1 & word2;
                    count += tab[andw & 0xff] +
                        tab[(andw >> 8) & 0xff] +
                        tab[(andw >> 16) & 0xff] +
                        tab[andw >> 24];

                    if (count >= threshold) return TRUE;
                    if (count + downcount[y] - untouchable < threshold) {
                        return FALSE;
                    }
                }
            } else {
                for (y = lorow; y < hirow; y++, row1 += wpl1, row2 += wpl2) {
                        /* Do the first iteration so the loop can be
                         * branch-free.  This section is the same as above
                         * except for the different limit on the loop, since
                         * the last iteration is the same as all the other
                         * iterations (beyond the first). */
                    word1 = row1[0];
                    word2 = row2[0] >> idelx;
                    andw = word1 & word2;
                    count += tab[andw & 0xff] +
                        tab[(andw >> 8) & 0xff] +
                        tab[(andw >> 16) & 0xff] +
                        tab[andw >> 24];

                    for (x = 1; x < rowwords1; x++) {
                        word1 = row1[x];
                        word2 = (row2[x] >> idelx) |
                            (row2[x - 1] << (32 - idelx));
                        andw = word1 & word2;
                        count += tab[andw & 0xff] +
                            tab[(andw >> 8) & 0xff] +
                            tab[(andw >> 16) & 0xff] +
                            tab[andw >> 24];
                    }

                    if (count >= threshold) return TRUE;
                    if (count + downcount[y] - untouchable < threshold) {
                        return FALSE;
                    }
                }
            }
        } else {
                /* pix2 is shifted to the left.  word 0 of pix1 is touched by
                 * word 0 and word 1 of pix2, and so on up to the last word of
                 * pix1 (word N), which is touched by words N and N+1 of
                 * pix2... if there is a word N+1.  Handle the two cases (pix2
                 * has N words and pix2 has at least N+1 words) separately. */
            if (rowwords1 < rowwords2) {
                    /* pix2 has at least N+1 words, so every iteration through
                     * the loop can be the same. */
                for (y = lorow; y < hirow; y++, row1 += wpl1, row2 += wpl2) {
                    for (x = 0; x < rowwords1; x++) {
                        word1 = row1[x];
                        word2 = row2[x] << -idelx;
                        word2 |= row2[x + 1] >> (32 + idelx);
                        andw = word1 & word2;
                        count += tab[andw & 0xff] +
                            tab[(andw >> 8) & 0xff] +
                            tab[(andw >> 16) & 0xff] +
                            tab[andw >> 24];
                    }

                    if (count >= threshold) return TRUE;
                    if (count + downcount[y] - untouchable < threshold) {
                        return FALSE;
                    }
                }
            } else {
                    /* pix2 has only N words, so the last iteration is broken
                     * out. */
                for (y = lorow; y < hirow; y++, row1 += wpl1, row2 += wpl2) {
                    for (x = 0; x < rowwords1 - 1; x++) {
                        word1 = row1[x];
                        word2 = row2[x] << -idelx;
                        word2 |= row2[x + 1] >> (32 + idelx);
                        andw = word1 & word2;
                        count += tab[andw & 0xff] +
                            tab[(andw >> 8) & 0xff] +
                            tab[(andw >> 16) & 0xff] +
                            tab[andw >> 24];
                    }

                    word1 = row1[x];
                    word2 = row2[x] << -idelx;
                    andw = word1 & word2;
                    count += tab[andw & 0xff] +
                        tab[(andw >> 8) & 0xff] +
                        tab[(andw >> 16) & 0xff] +
                        tab[andw >> 24];

                    if (count >= threshold) return TRUE;
                    if (count + downcount[y] - untouchable < threshold) {
                        return FALSE;
                    }
                }
            }
        }
    }

    score = (l_float32)(count * count) / (l_float32)(area1 * area2);
    if (score >= score_threshold) {
        fprintf(stderr, "count %d < threshold %d but score %g >= score_threshold %g\n",
                count, threshold, score, score_threshold);
    }
    return FALSE;
}


/*!
 *  pixCorrelationScoreSimple()
 *
 *      Input:  pix1   (test pix, 1 bpp)
 *              pix2   (exemplar pix, 1 bpp)
 *              area1  (number of on pixels in pix1)
 *              area2  (number of on pixels in pix2)
 *              delx   (x comp of centroid difference)
 *              dely   (y comp of centroid difference)
 *              maxdiffw (max width difference of pix1 and pix2)
 *              maxdiffh (max height difference of pix1 and pix2)
 *              tab    (sum tab for byte)
 *      Return: correlation score 
 *
 *  Notes:
 *      (1) This calculates exactly the same value as pixCorrelationScore().
 *          It is 2-3x slower, but much simpler to understand.
 */
l_float32
pixCorrelationScoreSimple(PIX       *pix1,
                          PIX       *pix2,
                          l_int32    area1,
                          l_int32    area2,
                          l_float32  delx,   /* x(1) - x(3) */
                          l_float32  dely,   /* y(1) - y(3) */
                          l_int32    maxdiffw,
                          l_int32    maxdiffh,
                          l_int32   *tab)
{
l_int32    wi, hi, wt, ht, delw, delh, idelx, idely, count;
l_float32  score;
PIX       *pixt;

    PROCNAME("pixCorrelationScoreSimple");

    if (!pix1 || pixGetDepth(pix1) != 1)
        return (l_float32)ERROR_FLOAT("pix1 not 1 bpp", procName, 0.0);
    if (!pix2 || pixGetDepth(pix2) != 1)
        return (l_float32)ERROR_FLOAT("pix2 not 1 bpp", procName, 0.0);
    if (!tab)
        return (l_float32)ERROR_FLOAT("tab not defined", procName, 0.0);
    if (!area1 || !area2)
        return (l_float32)ERROR_FLOAT("areas must be > 0", procName, 0.0);

        /* Eliminate based on size difference */
    pixGetDimensions(pix1, &wi, &hi, NULL);
    pixGetDimensions(pix2, &wt, &ht, NULL);
    delw = L_ABS(wi - wt);
    if (delw > maxdiffw)
        return 0.0;
    delh = L_ABS(hi - ht);
    if (delh > maxdiffh)
        return 0.0;

        /* Round difference to nearest integer */
    if (delx >= 0)
        idelx = (l_int32)(delx + 0.5);
    else
        idelx = (l_int32)(delx - 0.5);
    if (dely >= 0)
        idely = (l_int32)(dely + 0.5);
    else
        idely = (l_int32)(dely - 0.5);

        /*  pixt = pixAnd(NULL, pix1, pix2), including shift.
         *  To insure that pixels are ON only within the
         *  intersection of pix1 and the shifted pix2:
         *  (1) Start with pixt cleared and equal in size to pix1.
         *  (2) Blit the shifted pix2 onto pixt.  Then all ON pixels
         *      are within the intersection of pix1 and the shifted pix2.
         *  (3) AND pix1 with pixt. */
    pixt = pixCreateTemplate(pix1);
    pixRasterop(pixt, idelx, idely, wt, ht, PIX_SRC, pix2, 0, 0);
    pixRasterop(pixt, 0, 0, wi, hi, PIX_SRC & PIX_DST, pix1, 0, 0);
    pixCountPixels(pixt, &count, tab);
    pixDestroy(&pixt);

    score = (l_float32)(count * count) / (l_float32)(area1 * area2);
/*    fprintf(stderr, "score = %7.3f, count = %d, area1 = %d, area2 = %d\n",
             score, count, area1, area2); */
    return score;
}
