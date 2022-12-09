(function (window, document, $, undefined) {
	'use strict';

	function create_$fake(text) {
		var $fake = $('<textarea />');

		$fake.css({
			fontSize: '12pt',
			position: 'fixed',
			top     : '100%'
		});

		$fake.prop('readonly', true);

		$fake.val(text);

		return $fake;
	}

	function select($element) {
		var element    = $element.get(0);
		var isReadOnly = $element.prop('readonly');

		if (!isReadOnly) {
			$element.prop('readonly', true);
		}

		element.select();
		element.setSelectionRange(0, $element.val().length);

		if (!isReadOnly) {
			$element.prop('readonly', false);
		}

		return $element.val();
	}

	function exec_copy() {
		var succeeded;

		try {
			succeeded = document.execCommand('copy');
		} catch (err) {
			succeeded = false;
		}

		return succeeded;
	}

	function copy(text) {
		var $container = $('body');

		var $fake = create_$fake(text);

		$container.append($fake);

		select($fake);

		if (!exec_copy()) {
			return false;
		}

		window.getSelection().removeAllRanges();

		$fake.remove();

		return true;
	}

	function onClick(event) {
		var $element = $(this);
		var text     = $element.attr('data-st-copy-text');

		event.preventDefault();

		if (copy(text)) {
			$element.focus();

			alert('記事タイトルとURLをコピーしました');
		} else {
			alert('ご利用の環境はコピーに対応していません');
		}
	}

	function onReady() {
		$('[data-st-copy-text]').each(function (index, element) {
			$(element).on('click', onClick);
		});
	}

	$(onReady);
}(window, window.document, jQuery));
