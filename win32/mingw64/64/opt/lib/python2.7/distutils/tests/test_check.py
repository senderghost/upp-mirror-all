# -*- encoding: utf8 -*-
"""Tests for distutils.command.check."""
import unittest
from test.test_support import run_unittest

from distutils.command.check import check, HAS_DOCUTILS
from distutils.tests import support
from distutils.errors import DistutilsSetupError

class CheckTestCase(support.LoggingSilencer,
                    support.TempdirManager,
                    unittest.TestCase):

    def _run(self, metadata=None, **options):
        if metadata is None:
            metadata = {}
        pkg_info, dist = self.create_dist(**metadata)
        cmd = check(dist)
        cmd.initialize_options()
        for name, value in options.items():
            setattr(cmd, name, value)
        cmd.ensure_finalized()
        cmd.run()
        return cmd

    def test_check_metadata(self):
        # let's run the command with no metadata at all
        # by default, check is checking the metadata
        # should have some warnings
        cmd = self._run()
        self.assertEqual(cmd._warnings, 2)

        # now let's add the required fields
        # and run it again, to make sure we don't get
        # any warning anymore
        metadata = {'url': 'xxx', 'author': 'xxx',
                    'author_email': 'xxx',
                    'name': 'xxx', 'version': 'xxx'}
        cmd = self._run(metadata)
        self.assertEqual(cmd._warnings, 0)

        # now with the strict mode, we should
        # get an error if there are missing metadata
        self.assertRaises(DistutilsSetupError, self._run, {}, **{'strict': 1})

        # and of course, no error when all metadata are present
        cmd = self._run(metadata, strict=1)
        self.assertEqual(cmd._warnings, 0)

        # now a test with Unicode entries
        metadata = {'url': u'xxx', 'author': u'\u00c9ric',
                    'author_email': u'xxx', u'name': 'xxx',
                    'version': u'xxx',
                    'description': u'Something about esszet \u00df',
                    'long_description': u'More things about esszet \u00df'}
        cmd = self._run(metadata)
        self.assertEqual(cmd._warnings, 0)

    @unittest.skipUnless(HAS_DOCUTILS, "won't test without docutils")
    def test_check_document(self):
        pkg_info, dist = self.create_dist()
        cmd = check(dist)

        # let's see if it detects broken rest
        broken_rest = 'title\n===\n\ntest'
        msgs = cmd._check_rst_data(broken_rest)
        self.assertEqual(len(msgs), 1)

        # and non-broken rest
        rest = 'title\n=====\n\ntest'
        msgs = cmd._check_rst_data(rest)
        self.assertEqual(len(msgs), 0)

    @unittest.skipUnless(HAS_DOCUTILS, "won't test without docutils")
    def test_check_restructuredtext(self):
        # let's see if it detects broken rest in long_description
        broken_rest = 'title\n===\n\ntest'
        pkg_info, dist = self.create_dist(long_description=broken_rest)
        cmd = check(dist)
        cmd.check_restructuredtext()
        self.assertEqual(cmd._warnings, 1)

        # let's see if we have an error with strict=1
        metadata = {'url': 'xxx', 'author': 'xxx',
                    'author_email': 'xxx',
                    'name': 'xxx', 'version': 'xxx',
                    'long_description': broken_rest}
        self.assertRaises(DistutilsSetupError, self._run, metadata,
                          **{'strict': 1, 'restructuredtext': 1})

        # and non-broken rest, including a non-ASCII character to test #12114
        metadata['long_description'] = u'title\n=====\n\ntest \u00df'
        cmd = self._run(metadata, strict=1, restructuredtext=1)
        self.assertEqual(cmd._warnings, 0)

    def test_check_all(self):

        metadata = {'url': 'xxx', 'author': 'xxx'}
        self.assertRaises(DistutilsSetupError, self._run,
                          {}, **{'strict': 1,
                                 'restructuredtext': 1})

def test_suite():
    return unittest.makeSuite(CheckTestCase)

if __name__ == "__main__":
    run_unittest(test_suite())
