<?hh // strict
namespace Fastuc\I18n
{
	class Translator
	{
		/**
		 * @var \gettext_reader
		 */
		private \gettext_reader $reader;

		/**
		 * @param string $file
		 */
		public function loadFile( string $file ) : void
		{
			if( false === file_exists( $file ) )
			{
				throw new Exception( 'Translation file does not exist: ' . $file );
			}

			require_once 'gettext/streams.php';
			require_once 'gettext/gettext.php';

			$streamer = new \FileReader( $file );
			$this->reader = new \gettext_reader( $streamer );
		}

		/**
		 * @param string $literal
		 * @return string
		 */
		public function translate( string $literal ) : string
		{
			return $this->reader->translate( $literal );
		}
	}
}

namespace
{
	if( !function_exists( 'getCurrentLocale' ) )
	{
		/**
		 * @return string
		 */
		function getCurrentLocale() : string
		{
			return isset( $GLOBALS['currentLocale'] ) ? $GLOBALS['currentLocale'] : 'en';

		}
	}

	/**
	 * Translates an string using the current locale.
	 *
	 * @param string $id Original string identifier.
	 * @return string
	 */
	function __( string $id ) : string
	{
		/**
		 * @var \Fastuc\I18n\Translator
		 */
		static $translator = null;

		if( null === $translator )
		{
			$currentLocale = getCurrentLocale();
			$path = APP_PATH . '/locales/' . $currentLocale . '/messages.mo';

			$translator = new \Fastuc\I18n\Translator;
			$translator->loadFile( $path );
		}

		return $translator->translate( $id );
	}
}

